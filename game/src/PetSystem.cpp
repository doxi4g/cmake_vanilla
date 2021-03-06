#include "stdafx.h"
#include "utils.h"
#include "vector.h"
#include "char.h"
#include "sectree_manager.h"
#include "char_manager.h"
#include "mob_manager.h"
#include "PetSystem.h"
#include "../../common/VnumHelper.h"
#include "packet.h"
#include "item_manager.h"
#include "item.h"


extern int passes_per_sec;
EVENTINFO(petsystem_event_info)
{
	CPetSystem* pPetSystem;
};

// PetSystemÀ» update ÇØÁÖ´Â event.
// PetSystemÀº CHRACTER_MANAGER¿¡¼­ ±âÁ¸ FSMÀ¸·Î update ÇØÁÖ´Â ±âÁ¸ chracters¿Í ´Þ¸®,
// OwnerÀÇ STATE¸¦ update ÇÒ ¶§ _UpdateFollowAI ÇÔ¼ö·Î update ÇØÁØ´Ù.
// ±×·±µ¥ ownerÀÇ state¸¦ update¸¦ CHRACTER_MANAGER¿¡¼­ ÇØÁÖ±â ¶§¹®¿¡,
// petsystemÀ» updateÇÏ´Ù°¡ petÀ» unsummonÇÏ´Â ºÎºÐ¿¡¼­ ¹®Á¦°¡ »ý°å´Ù.
// (CHRACTER_MANAGER¿¡¼­ update ÇÏ¸é chracter destroy°¡ pendingµÇ¾î, CPetSystem¿¡¼­´Â dangling Æ÷ÀÎÅÍ¸¦ °¡Áö°í ÀÖ°Ô µÈ´Ù.)
// µû¶ó¼­ PetSystem¸¸ ¾÷µ¥ÀÌÆ® ÇØÁÖ´Â event¸¦ ¹ß»ý½ÃÅ´.
EVENTFUNC(petsystem_update_event)
{
	petsystem_event_info* info = dynamic_cast<petsystem_event_info*>( event->info );
	if ( info == NULL )
	{
		sys_err( "check_speedhack_event> <Factor> Null pointer" );
		return 0;
	}

	CPetSystem*	pPetSystem = info->pPetSystem;

	if (NULL == pPetSystem)
		return 0;

	
	pPetSystem->Update(0);
	// 0.25ÃÊ¸¶´Ù °»½Å.
	return PASSES_PER_SEC(1) / 4;
}

///////////////////////////////////////////////////////////////////////////////////////
//  CPetActor
///////////////////////////////////////////////////////////////////////////////////////

CPetActor::CPetActor(LPCHARACTER owner, DWORD vnum, DWORD options)
{
	m_dwVnum = vnum;
	m_dwVID = 0;
	m_dwOptions = options;
	m_dwLastActionTime = 0;

	m_pkChar = 0;
	m_pkOwner = owner;

	m_originalMoveSpeed = 0;
	
	m_dwSummonItemVID = 0;
	m_dwSummonItemVnum = 0;
}

CPetActor::~CPetActor()
{
	this->Unsummon();

	m_pkOwner = 0;
}

void CPetActor::SetName(const char* name)
{
	std::string petName = m_pkOwner->GetName();

	if (0 != m_pkOwner && 
		0 == name && 
		0 != m_pkOwner->GetName())
	{
		petName += "'s Pet";
	}
	else
		petName += name;

	if (true == IsSummoned())
		m_pkChar->SetName(petName);

	m_name = petName;
}

bool CPetActor::Mount()
{
	if (0 == m_pkOwner)
		return false;

	if (true == HasOption(EPetOption_Mountable))
		m_pkOwner->MountVnum(m_dwVnum);

	return m_pkOwner->GetMountVnum() == m_dwVnum;;
}

void CPetActor::Unmount()
{
	if (0 == m_pkOwner)
		return;

	if (m_pkOwner->IsHorseRiding())
		m_pkOwner->StopRiding();
}

void CPetActor::Unsummon()
{
	if (true == this->IsSummoned())
	{
		// ¹öÇÁ »èÁ¦
		this->ClearBuff();
		this->SetSummonItem(NULL);
		if (NULL != m_pkOwner)
			m_pkOwner->ComputePoints();

		if (NULL != m_pkChar)
			M2_DESTROY_CHARACTER(m_pkChar);

		m_pkChar = 0;
		m_dwVID = 0;
	}
}

DWORD CPetActor::Summon(const char* petName, LPITEM pSummonItem, bool bSpawnFar)
{
	long x = m_pkOwner->GetX();
	long y = m_pkOwner->GetY();
	long z = m_pkOwner->GetZ();

	if (true == bSpawnFar)
	{
		x += (number(0, 1) * 2 - 1) * number(2000, 2500);
		y += (number(0, 1) * 2 - 1) * number(2000, 2500);
	}
	else
	{
		x += number(-100, 100);
		y += number(-100, 100);
	}

	if (0 != m_pkChar)
	{
		m_pkChar->Show (m_pkOwner->GetMapIndex(), x, y);
		m_dwVID = m_pkChar->GetVID();

		return m_dwVID;
	}
	
	m_pkChar = CHARACTER_MANAGER::instance().SpawnMob(
				m_dwVnum, 
				m_pkOwner->GetMapIndex(), 
				x, y, z,
				false, (int)(m_pkOwner->GetRotation()+180), false);

	if (0 == m_pkChar)
	{
		sys_err("[CPetSystem::Summon] Failed to summon the pet. (vnum: %d)", m_dwVnum);
		return 0;
	}

	m_pkChar->SetPet();

//	m_pkOwner->DetailLog();
//	m_pkChar->DetailLog();

	//ÆêÀÇ ±¹°¡¸¦ ÁÖÀÎÀÇ ±¹°¡·Î ¼³Á¤ÇÔ.
	m_pkChar->SetEmpire(m_pkOwner->GetEmpire());

	m_dwVID = m_pkChar->GetVID();

	this->SetName(petName);

	// SetSummonItem(pSummonItem)¸¦ ºÎ¸¥ ÈÄ¿¡ ComputePoints¸¦ ºÎ¸£¸é ¹öÇÁ Àû¿ëµÊ.
	this->SetSummonItem(pSummonItem);
	m_pkOwner->ComputePoints();
	m_pkChar->Show(m_pkOwner->GetMapIndex(), x, y, z);

	return m_dwVID;
}

bool CPetActor::_UpdatAloneActionAI(float fMinDist, float fMaxDist)
{
	float fDist = number(fMinDist, fMaxDist);
	float r = (float)number (0, 359);
	float dest_x = GetOwner()->GetX() + fDist * cos(r);
	float dest_y = GetOwner()->GetY() + fDist * sin(r);

	//m_pkChar->SetRotation(number(0, 359));        // ¹æÇâÀº ·£´ýÀ¸·Î ¼³Á¤

	//GetDeltaByDegree(m_pkChar->GetRotation(), fDist, &fx, &fy);

	// ´À½¼ÇÑ ¸ø°¨ ¼Ó¼º Ã¼Å©; ÃÖÁ¾ À§Ä¡¿Í Áß°£ À§Ä¡°¡ °¥¼ö¾ø´Ù¸é °¡Áö ¾Ê´Â´Ù.
	//if (!(SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy) 
	//			&& SECTREE_MANAGER::instance().IsMovablePosition(m_pkChar->GetMapIndex(), m_pkChar->GetX() + (int) fx/2, m_pkChar->GetY() + (int) fy/2)))
	//	return true;

	m_pkChar->SetNowWalking(true);

	//if (m_pkChar->Goto(m_pkChar->GetX() + (int) fx, m_pkChar->GetY() + (int) fy))
	//	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	if (!m_pkChar->IsStateMove() && m_pkChar->Goto(dest_x, dest_y))
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);

	m_dwLastActionTime = get_dword_time();

	return true;
}

// char_state.cpp StateHorseÇÔ¼ö ±×³É C&P -_-;
bool CPetActor::_UpdateFollowAI()
{
	if (0 == m_pkChar->m_pkMobData)
	{
		//sys_err("[CPetActor::_UpdateFollowAI] m_pkChar->m_pkMobData is NULL");
		return false;
	}
	
	// NOTE: Ä³¸¯ÅÍ(Æê)ÀÇ ¿ø·¡ ÀÌµ¿ ¼Óµµ¸¦ ¾Ë¾Æ¾ß ÇÏ´Âµ¥, ÇØ´ç °ª(m_pkChar->m_pkMobData->m_table.sMovingSpeed)À» Á÷Á¢ÀûÀ¸·Î Á¢±ÙÇØ¼­ ¾Ë¾Æ³¾ ¼öµµ ÀÖÁö¸¸
	// m_pkChar->m_pkMobData °ªÀÌ invalidÇÑ °æ¿ì°¡ ÀÚÁÖ ¹ß»ýÇÔ. ÇöÀç ½Ã°£°ü°è»ó ¿øÀÎÀº ´ÙÀ½¿¡ ÆÄ¾ÇÇÏ°í ÀÏ´ÜÀº m_pkChar->m_pkMobData °ªÀ» ¾Æ¿¹ »ç¿ëÇÏÁö ¾Êµµ·Ï ÇÔ.
	// ¿©±â¼­ ¸Å¹ø °Ë»çÇÏ´Â ÀÌÀ¯´Â ÃÖÃÊ ÃÊ±âÈ­ ÇÒ ¶§ Á¤»ó °ªÀ» Á¦´ë·Î ¸ø¾ò¾î¿À´Â °æ¿ìµµ ÀÖÀ½.. -_-;; ¤Ð¤Ð¤Ð¤Ð¤Ð¤Ð¤Ð¤Ð¤Ð
	if (0 == m_originalMoveSpeed)
	{
		const CMob* mobData = CMobManager::Instance().Get(m_dwVnum);

		if (0 != mobData)
			m_originalMoveSpeed = mobData->m_table.sMovingSpeed;
	}
	float	START_FOLLOW_DISTANCE = 300.0f;		// ÀÌ °Å¸® ÀÌ»ó ¶³¾îÁö¸é ÂÑ¾Æ°¡±â ½ÃÀÛÇÔ
	float	START_RUN_DISTANCE = 900.0f;		// ÀÌ °Å¸® ÀÌ»ó ¶³¾îÁö¸é ¶Ù¾î¼­ ÂÑ¾Æ°¨.

	float	RESPAWN_DISTANCE = 4500.f;			// ÀÌ °Å¸® ÀÌ»ó ¸Ö¾îÁö¸é ÁÖÀÎ ¿·À¸·Î ¼ÒÈ¯ÇÔ.
	int		APPROACH = 200;						// Á¢±Ù °Å¸®

	bool bRun = false;							// ¶Ù¾î¾ß ÇÏ³ª?

	DWORD currentTime = get_dword_time();

	long ownerX = m_pkOwner->GetX();		long ownerY = m_pkOwner->GetY();
	long charX = m_pkChar->GetX();			long charY = m_pkChar->GetY();

	float fDist = DISTANCE_APPROX(charX - ownerX, charY - ownerY);

	if (fDist >= RESPAWN_DISTANCE)
	{
		float fOwnerRot = m_pkOwner->GetRotation() * 3.141592f / 180.f;
		float fx = -APPROACH * cos(fOwnerRot);
		float fy = -APPROACH * sin(fOwnerRot);
		if (m_pkChar->Show(m_pkOwner->GetMapIndex(), ownerX + fx, ownerY + fy))
		{
			return true;
		}
	}
	
	
	if (fDist >= START_FOLLOW_DISTANCE)
	{
		if( fDist >= START_RUN_DISTANCE)
		{
			bRun = true;
		}

		m_pkChar->SetNowWalking(!bRun);		// NOTE: ÇÔ¼ö ÀÌ¸§º¸°í ¸ØÃß´Â°ÇÁÙ ¾Ë¾Ò´Âµ¥ SetNowWalking(false) ÇÏ¸é ¶Ù´Â°ÅÀÓ.. -_-;
		
		Follow(APPROACH);

		m_pkChar->SetLastAttacked(currentTime);
		m_dwLastActionTime = currentTime;
	}
	//else
	//{
	//	if (fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) > 10.f || fabs(m_pkChar->GetRotation() - GetDegreeFromPositionXY(charX, charY, ownerX, ownerX)) < 350.f)
	//	{
	//		m_pkChar->Follow(m_pkOwner, APPROACH);
	//		m_pkChar->SetLastAttacked(currentTime);
	//		m_dwLastActionTime = currentTime;
	//	}
	//}
	// Follow ÁßÀÌÁö¸¸ ÁÖÀÎ°ú ÀÏÁ¤ °Å¸® ÀÌ³»·Î °¡±î¿öÁ³´Ù¸é ¸ØÃã
	else 
		m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0);
	//else if (currentTime - m_dwLastActionTime > number(5000, 12000))
	//{
	//	this->_UpdatAloneActionAI(START_FOLLOW_DISTANCE / 2, START_FOLLOW_DISTANCE);
	//}

	return true;
}

bool CPetActor::Update(DWORD deltaTime)
{
	bool bResult = true;

	// Æê ÁÖÀÎÀÌ Á×¾ú°Å³ª, ¼ÒÈ¯µÈ ÆêÀÇ »óÅÂ°¡ ÀÌ»óÇÏ´Ù¸é ÆêÀ» ¾ø¾Ú. (NOTE: °¡²û°¡´Ù ÀÌ·± Àú·± ÀÌÀ¯·Î ¼ÒÈ¯µÈ ÆêÀÌ DEAD »óÅÂ¿¡ ºüÁö´Â °æ¿ì°¡ ÀÖÀ½-_-;)
	// ÆêÀ» ¼ÒÈ¯ÇÑ ¾ÆÀÌÅÛÀÌ ¾ø°Å³ª, ³»°¡ °¡Áø »óÅÂ°¡ ¾Æ´Ï¶ó¸é ÆêÀ» ¾ø¾Ú.
	if (m_pkOwner->IsDead() || (IsSummoned() && m_pkChar->IsDead()) 
		|| NULL == ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())
		|| ITEM_MANAGER::instance().FindByVID(this->GetSummonItemVID())->GetOwner() != this->GetOwner()
		)
	{
		this->Unsummon();
		return true;
	}

	if (this->IsSummoned() && HasOption(EPetOption_Followable))
		bResult = bResult && this->_UpdateFollowAI();

	return bResult;
}

//NOTE : ÁÖÀÇ!!! MinDistance¸¦ Å©°Ô ÀâÀ¸¸é ±× º¯À§¸¸Å­ÀÇ º¯È­µ¿¾ÈÀº followÇÏÁö ¾Ê´Â´Ù,
bool CPetActor::Follow(float fMinDistance)
{
	// °¡·Á´Â À§Ä¡¸¦ ¹Ù¶óºÁ¾ß ÇÑ´Ù.
	if( !m_pkOwner || !m_pkChar) 
		return false;

	float fOwnerX = m_pkOwner->GetX();
	float fOwnerY = m_pkOwner->GetY();

	float fPetX = m_pkChar->GetX();
	float fPetY = m_pkChar->GetY();

	float fDist = DISTANCE_SQRT(fOwnerX - fPetX, fOwnerY - fPetY);
	if (fDist <= fMinDistance)
		return false;

	m_pkChar->SetRotationToXY(fOwnerX, fOwnerY);

	float fx, fy;

	float fDistToGo = fDist - fMinDistance;
	GetDeltaByDegree(m_pkChar->GetRotation(), fDistToGo, &fx, &fy);
	
	if (!m_pkChar->Goto((int)(fPetX+fx+0.5f), (int)(fPetY+fy+0.5f)) )
		return false;

	m_pkChar->SendMovePacket(FUNC_WAIT, 0, 0, 0, 0, 0);

	return true;
}

void CPetActor::SetSummonItem (LPITEM pItem)
{
	if (NULL == pItem)
	{
		m_dwSummonItemVID = 0;
		m_dwSummonItemVnum = 0;
		return;
	}

	m_dwSummonItemVID = pItem->GetVID();
	m_dwSummonItemVnum = pItem->GetVnum();
}

void CPetActor::GiveBuff()
{
	// ÆÄÈ² Æê ¹öÇÁ´Â ´øÀü¿¡¼­¸¸ ¹ß»ýÇÔ.
	if (34004 == m_dwVnum || 34009 == m_dwVnum)
	{
		if (NULL == m_pkOwner->GetDungeon())
		{
			return;
		}
	}
	LPITEM item = ITEM_MANAGER::instance().FindByVID(m_dwSummonItemVID);
	if (NULL != item)
		item->ModifyPoints(true);
	return ;
}

void CPetActor::ClearBuff()
{
	if (NULL == m_pkOwner)
		return ;
	TItemTable* item_proto = ITEM_MANAGER::instance().GetTable(m_dwSummonItemVnum);
	if (NULL == item_proto)
		return;
	for (int i = 0; i < ITEM_APPLY_MAX_NUM; i++)
	{
		if (item_proto->aApplies[i].bType == APPLY_NONE)
			continue;
		m_pkOwner->ApplyPoint(item_proto->aApplies[i].bType, -item_proto->aApplies[i].lValue);
	}

	return ;
}

///////////////////////////////////////////////////////////////////////////////////////
//  CPetSystem
///////////////////////////////////////////////////////////////////////////////////////

CPetSystem::CPetSystem(LPCHARACTER owner)
{
//	assert(0 != owner && "[CPetSystem::CPetSystem] Invalid owner");

	m_pkOwner = owner;
	m_dwUpdatePeriod = 400;

	m_dwLastUpdateTime = 0;
}

CPetSystem::~CPetSystem()
{
	Destroy();
}

void CPetSystem::Destroy()
{
	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			delete petActor;
		}
	}
	event_cancel(&m_pkPetSystemUpdateEvent);
	m_petActorMap.clear();
}

/// Æê ½Ã½ºÅÛ ¾÷µ¥ÀÌÆ®. µî·ÏµÈ ÆêµéÀÇ AI Ã³¸® µîÀ» ÇÔ.
bool CPetSystem::Update(DWORD deltaTime)
{
	bool bResult = true;

	DWORD currentTime = get_dword_time();

	// CHARACTER_MANAGER¿¡¼­ Ä³¸¯ÅÍ·ù UpdateÇÒ ¶§ ¸Å°³º¯¼ö·Î ÁÖ´Â (Pulse¶ó°í µÇ¾îÀÖ´Â)°ªÀÌ ÀÌÀü ÇÁ·¹ÀÓ°úÀÇ ½Ã°£Â÷ÀÌÀÎÁÙ ¾Ë¾Ò´Âµ¥
	// ÀüÇô ´Ù¸¥ °ªÀÌ¶ó¼­-_-; ¿©±â¿¡ ÀÔ·ÂÀ¸·Î µé¾î¿À´Â deltaTimeÀº ÀÇ¹Ì°¡ ¾øÀ½¤Ð¤Ð	
	
	if (m_dwUpdatePeriod > currentTime - m_dwLastUpdateTime)
		return true;
	
	std::vector <CPetActor*> v_garbageActor;

	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor && petActor->IsSummoned())
		{
			LPCHARACTER pPet = petActor->GetCharacter();
			
			if (NULL == CHARACTER_MANAGER::instance().Find(pPet->GetVID()))
			{
				v_garbageActor.push_back(petActor);
			}
			else
			{
				bResult = bResult && petActor->Update(deltaTime);
			}
		}
	}
	for (std::vector<CPetActor*>::iterator it = v_garbageActor.begin(); it != v_garbageActor.end(); it++)
		DeletePet(*it);

	m_dwLastUpdateTime = currentTime;

	return bResult;
}

/// °ü¸® ¸ñ·Ï¿¡¼­ ÆêÀ» Áö¿ò
void CPetSystem::DeletePet(DWORD mobVnum)
{
	TPetActorMap::iterator iter = m_petActorMap.find(mobVnum);

	if (m_petActorMap.end() == iter)
	{
		sys_err("[CPetSystem::DeletePet] Can't find pet on my list (VNUM: %d)", mobVnum);
		return;
	}

	CPetActor* petActor = iter->second;

	if (0 == petActor)
		sys_err("[CPetSystem::DeletePet] Null Pointer (petActor)");
	else
		delete petActor;

	m_petActorMap.erase(iter);	
}

/// °ü¸® ¸ñ·Ï¿¡¼­ ÆêÀ» Áö¿ò
void CPetSystem::DeletePet(CPetActor* petActor)
{
	for (TPetActorMap::iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		if (iter->second == petActor)
		{
			delete petActor;
			m_petActorMap.erase(iter);

			return;
		}
	}

	sys_err("[CPetSystem::DeletePet] Can't find petActor(0x%x) on my list(size: %d) ", petActor, m_petActorMap.size());
}

void CPetSystem::Unsummon(DWORD vnum, bool bDeleteFromList)
{
	CPetActor* actor = this->GetByVnum(vnum);

	if (0 == actor)
	{
		sys_err("[CPetSystem::GetByVnum(%d)] Null Pointer (petActor)", vnum);
		return;
	}
	actor->Unsummon();

	if (true == bDeleteFromList)
		this->DeletePet(actor);

	bool bActive = false;
	for (TPetActorMap::iterator it = m_petActorMap.begin(); it != m_petActorMap.end(); it++)
	{
		bActive |= it->second->IsSummoned();
	}
	if (false == bActive)
	{
		event_cancel(&m_pkPetSystemUpdateEvent);
		m_pkPetSystemUpdateEvent = NULL;
	}
}


CPetActor* CPetSystem::Summon(DWORD mobVnum, LPITEM pSummonItem, const char* petName, bool bSpawnFar, DWORD options)
{
	CPetActor* petActor = this->GetByVnum(mobVnum);

	// µî·ÏµÈ ÆêÀÌ ¾Æ´Ï¶ó¸é »õ·Î »ý¼º ÈÄ °ü¸® ¸ñ·Ï¿¡ µî·ÏÇÔ.
	if (0 == petActor)
	{
		petActor = M2_NEW CPetActor(m_pkOwner, mobVnum, options);
		m_petActorMap.insert(std::make_pair(mobVnum, petActor));
	}

	petActor->Summon(petName, pSummonItem, bSpawnFar);

	if (NULL == m_pkPetSystemUpdateEvent)
	{
		petsystem_event_info* info = AllocEventInfo<petsystem_event_info>();

		info->pPetSystem = this;

		m_pkPetSystemUpdateEvent = event_create(petsystem_update_event, info, PASSES_PER_SEC(1) / 4);	// 0.25ÃÊ	
	}

	return petActor;
}


CPetActor* CPetSystem::GetByVID(DWORD vid) const
{
	CPetActor* petActor = 0;

	bool bFound = false;

	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		petActor = iter->second;

		if (0 == petActor)
		{
			sys_err("[CPetSystem::GetByVID(%d)] Null Pointer (petActor)", vid);
			continue;
		}

		bFound = petActor->GetVID() == vid;

		if (true == bFound)
			break;
	}

	return bFound ? petActor : 0;
}

/// µî·Ï µÈ Æê Áß¿¡¼­ ÁÖ¾îÁø ¸÷ VNUMÀ» °¡Áø ¾×ÅÍ¸¦ ¹ÝÈ¯ÇÏ´Â ÇÔ¼ö.
CPetActor* CPetSystem::GetByVnum(DWORD vnum) const
{
	CPetActor* petActor = 0;

	TPetActorMap::const_iterator iter = m_petActorMap.find(vnum);

	if (m_petActorMap.end() != iter)
		petActor = iter->second;

	return petActor;
}

size_t CPetSystem::CountSummoned() const
{
	size_t count = 0;

	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
				++count;
		}
	}

	return count;
}

void CPetSystem::RefreshBuff()
{
	for (TPetActorMap::const_iterator iter = m_petActorMap.begin(); iter != m_petActorMap.end(); ++iter)
	{
		CPetActor* petActor = iter->second;

		if (0 != petActor)
		{
			if (petActor->IsSummoned())
			{
				petActor->GiveBuff();
			}
		}
	}
}