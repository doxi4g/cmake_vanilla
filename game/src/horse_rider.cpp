#include "stdafx.h"
#include "constants.h"
#include "utils.h"
#include "horse_rider.h"
#include "config.h"
#include "char_manager.h"

const int HORSE_HEALTH_DROP_INTERVAL = 3 * 24 * 60 * 60;
const int HORSE_STAMINA_CONSUME_INTERVAL = 6 * 60;
const int HORSE_STAMINA_REGEN_INTERVAL = 12 * 60;
extern int max_horse_level;
//const int HORSE_HP_DROP_INTERVAL = 60;
//const int HORSE_STAMINA_CONSUME_INTERVAL = 3;
//const int HORSE_STAMINA_REGEN_INTERVAL = 6;

extern THorseStat c_aHorseStat[51];

CHorseRider::CHorseRider()
{
	Initialize();
}

CHorseRider::~CHorseRider()
{
	Destroy();
}

void CHorseRider::Initialize()
{
	m_eventStaminaRegen = NULL;
	m_eventStaminaConsume = NULL;
	memset(&m_Horse, 0, sizeof(m_Horse));
}

void CHorseRider::Destroy()
{
	event_cancel(&m_eventStaminaRegen);
	event_cancel(&m_eventStaminaConsume);
}

void CHorseRider::EnterHorse()
{
	if (GetHorseLevel() <= 0)
		return;

	if (GetHorseHealth() <= 0)
		return;

	if (IsHorseRiding())
	{
		m_Horse.bRiding = !m_Horse.bRiding;
		StartRiding();
	}
	else
	{
		StartStaminaRegenEvent();
	}
	CheckHorseHealthDropTime(false);
}

bool CHorseRider::ReviveHorse()
{
	if (GetHorseLevel() <= 0)
		return false;

	if (GetHorseHealth()>0)
		return false;

	int level = GetHorseLevel();

	m_Horse.sHealth = c_aHorseStat[level].iMaxHealth;
	m_Horse.sStamina = c_aHorseStat[level].iMaxStamina;

	// 2005.03.24.ipkn.말 살린후 다시 죽는 현상 수정
	ResetHorseHealthDropTime();

	StartStaminaRegenEvent();
	return true;
}

short CHorseRider::GetHorseMaxHealth()
{
	int level = GetHorseLevel();
	return c_aHorseStat[level].iMaxHealth;
}

short CHorseRider::GetHorseMaxStamina()
{
	int level = GetHorseLevel();
	return c_aHorseStat[level].iMaxStamina;
}

void CHorseRider::FeedHorse()
{
	// 말을 가지고 살아있을때만
	if (GetHorseLevel() > 0 && GetHorseHealth() > 0)
	{
		UpdateHorseHealth(+1);
		// 20050324. ipkn 말 먹였을때도 체력 감소 딜레이를 늘린다.
		ResetHorseHealthDropTime();
	}
}

void CHorseRider::SetHorseData(const THorseInfo& crInfo)
{
	m_Horse = crInfo;
}

// Stamina
void CHorseRider::UpdateHorseDataByLogoff(DWORD dwLogoffTime)
{
	if (GetHorseLevel() <= 0)
		return;

	if (dwLogoffTime >= 12 * 60)
		UpdateHorseStamina(dwLogoffTime / 12 / 60, false); // 로그오프 12분당 1씩 회복
}

void CHorseRider::UpdateHorseStamina(int iStamina, bool bSend)
{
	int level = GetHorseLevel();

	m_Horse.sStamina = MINMAX(0, m_Horse.sStamina + iStamina, c_aHorseStat[level].iMaxStamina);

	if (GetHorseStamina() == 0 && IsHorseRiding())
	{
		StopRiding();
	}

	if (bSend)
		SendHorseInfo();
}

bool CHorseRider::StartRiding()
{
	if (m_Horse.bRiding)
		return false;

	if (GetHorseLevel() <= 0)
		return false;

	if (GetHorseHealth() <= 0)
		return false;

	if (GetHorseStamina() <= 0)
		return false;

	m_Horse.bRiding = true;
	StartStaminaConsumeEvent();
	SendHorseInfo();
	return true;
}

bool CHorseRider::StopRiding()
{
	if (!m_Horse.bRiding)
		return false;

	m_Horse.bRiding = false;
	StartStaminaRegenEvent();
	return true;
}

EVENTINFO(horserider_info) 
{
	CHorseRider* hr;

	horserider_info() 
	: hr( 0 )
	{
	}
};

EVENTFUNC(horse_stamina_consume_event)
{
	horserider_info* info = dynamic_cast<horserider_info*>( event->info );

	if ( info == NULL )
	{
		sys_err( "horse_stamina_consume_event> <Factor> Null pointer" );
		return 0;
	}

	CHorseRider* hr = info->hr;

	if (hr->GetHorseHealth() <= 0)
	{
		hr->m_eventStaminaConsume = NULL;
		return 0;
	}

	hr->UpdateHorseStamina(-1);
	hr->UpdateRideTime(HORSE_STAMINA_CONSUME_INTERVAL);

	int delta = PASSES_PER_SEC(HORSE_STAMINA_CONSUME_INTERVAL);

	if (hr->GetHorseStamina() == 0)
	{
		hr->m_eventStaminaConsume = NULL;
		delta = 0;
	}

	hr->CheckHorseHealthDropTime();
	sys_log(0, "HORSE STAMINA - %p", get_pointer(event));
	return delta;
}

EVENTFUNC(horse_stamina_regen_event)
{
	horserider_info* info = dynamic_cast<horserider_info*>( event->info );

	if ( info == NULL )
	{
		sys_err( "horse_stamina_regen_event> <Factor> Null pointer" );
		return 0;
	}

	CHorseRider* hr = info->hr;

	if (hr->GetHorseHealth()<=0)
	{
		hr->m_eventStaminaRegen = NULL;
		return 0;
	}

	hr->UpdateHorseStamina(+1);
	int delta = PASSES_PER_SEC(HORSE_STAMINA_REGEN_INTERVAL);
	if (hr->GetHorseStamina() == hr->GetHorseMaxStamina())
	{
		delta = 0;
		hr->m_eventStaminaRegen = NULL;
	}

	hr->CheckHorseHealthDropTime();
	sys_log(0, "HORSE STAMINA + %p", get_pointer(event));


	return delta;
}

void CHorseRider::StartStaminaConsumeEvent()
{
	if (GetHorseLevel() <= 0)
		return;

	if (GetHorseHealth() <= 0)
		return;

	sys_log(0,"HORSE STAMINA REGEN EVENT CANCEL %p", get_pointer(m_eventStaminaRegen));
	event_cancel(&m_eventStaminaRegen);

	if (m_eventStaminaConsume)
		return;

	horserider_info* info = AllocEventInfo<horserider_info>();

	info->hr = this;
	m_eventStaminaConsume = event_create(horse_stamina_consume_event, info, PASSES_PER_SEC(HORSE_STAMINA_CONSUME_INTERVAL));
	sys_log(0,"HORSE STAMINA CONSUME EVENT CREATE %p", get_pointer(m_eventStaminaConsume));
}

void CHorseRider::StartStaminaRegenEvent()
{
	if (GetHorseLevel() <= 0)
		return;

	if (GetHorseHealth() <= 0)
		return;

	sys_log(0,"HORSE STAMINA CONSUME EVENT CANCEL %p", get_pointer(m_eventStaminaConsume));
	event_cancel(&m_eventStaminaConsume);

	if (m_eventStaminaRegen)
		return;

	horserider_info* info = AllocEventInfo<horserider_info>();

	info->hr = this;
	m_eventStaminaRegen = event_create(horse_stamina_regen_event, info, PASSES_PER_SEC(HORSE_STAMINA_REGEN_INTERVAL));
	sys_log(0,"HORSE STAMINA REGEN EVENT CREATE %p", get_pointer(m_eventStaminaRegen));
}

// Health
void CHorseRider::ResetHorseHealthDropTime()
{
	m_Horse.dwHorseHealthDropTime = get_global_time() + HORSE_HEALTH_DROP_INTERVAL;
}

void CHorseRider::CheckHorseHealthDropTime(bool bSend)
{
	DWORD now = get_global_time();

	while (m_Horse.dwHorseHealthDropTime < now)
	{
		m_Horse.dwHorseHealthDropTime += HORSE_HEALTH_DROP_INTERVAL;
		UpdateHorseHealth(-1, bSend);
	}
}

void CHorseRider::UpdateHorseHealth(int iHealth, bool bSend)
{
	int level = GetHorseLevel();

	m_Horse.sHealth = MINMAX(0, m_Horse.sHealth + iHealth, c_aHorseStat[level].iMaxHealth);

	if (level && m_Horse.sHealth == 0)
		HorseDie();

	if (bSend)
		SendHorseInfo();
}

void CHorseRider::HorseDie()
{
	sys_log(0, "HORSE DIE %p %p", get_pointer(m_eventStaminaRegen), get_pointer(m_eventStaminaConsume));
	UpdateHorseStamina(-m_Horse.sStamina);
	event_cancel(&m_eventStaminaRegen);
	event_cancel(&m_eventStaminaConsume);
}

void CHorseRider::SetHorseLevel(int iLevel)
{
	m_Horse.bLevel = iLevel = MINMAX(0, iLevel, max_horse_level);

	m_Horse.sStamina = c_aHorseStat[iLevel].iMaxStamina;
	m_Horse.sHealth = c_aHorseStat[iLevel].iMaxHealth;
	m_Horse.dwHorseHealthDropTime = 0;

	ResetHorseHealthDropTime();

	SendHorseInfo();
}

BYTE CHorseRider::GetHorseGrade()
{
	BYTE grade = 0;

	if (GetHorseLevel())
		grade = (GetHorseLevel() - 1) / 10 + 1;

	return grade;
}

