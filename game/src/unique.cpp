#include "stdafx.h"
#include "unique.h"
#include "char.h"
#include "char_manager.h"
#include "party.h"
#include "affect.h"
#include "packet.h"
#include "desc.h"
#include "config.h"
#include "regen.h"
#include "start_position.h"
#include "item.h"
#include "item_manager.h"
#include "utils.h"
#include "questmanager.h"

CUnique::CUnique(std::string id)
	: m_id(id)
{
	Initialize();
	//sys_log(0,"DUNGEON create orig %d real %d", lOriginalMapIndex, lMapIndex);
}

CUnique::~CUnique()
{
}

void CUnique::Initialize()
{
}

std::vector<DWORD> CUnique::MassGetUniqueVID()
{
	std::vector<DWORD> v_VIDLIST;
	for(const auto& i : m_map_UniqueMob)
	{
		v_VIDLIST.push_back(i.second->GetVID());
	}
	return v_VIDLIST;
}

void CUnique::UniqueSetMaxHP(const std::string& key, int iMaxHP)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key : %s", key.c_str());
		return;
	}
	it->second->SetMaxHP(iMaxHP);
}

void CUnique::UniqueMoveToPos(const std::string& key, int x, int y)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key : %s", key.c_str());
		return;
	}
	it->second->Goto(x, y);
}

void CUnique::UniqueSetHP(const std::string& key, int iHP)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key : %s", key.c_str());
		return;
	}
	it->second->SetHP(iHP);
}

void CUnique::UniqueSetDefGrade(const std::string& key, int iGrade)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key : %s", key.c_str());
		return;
	}
	it->second->PointChange(POINT_DEF_GRADE,iGrade - it->second->GetPoint(POINT_DEF_GRADE));
}

void CUnique::KillUnique(const std::string& key, LPCHARACTER pChar)
{
	bool already_dead = false;
	if(IsUniqueDead(key))
	{
		sys_err("KillUnique: Can not kill dead unique!");
		already_dead = true;
	}
	if(!pChar)
	{
		sys_err("KillUnique: Cowardly refusing to proceed without killer char!");
		return;
	}
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key or Dead: %s", key.c_str());
		return;
	}
	m_map_UniqueMob.erase(it);
	if(already_dead == false) {
		LPCHARACTER ch = it->second;
		if(!ch)
		{
			sys_err("KillUnique: Can not create a valid char pointer out of monster!!!");
			return;
		}
		ch->Dead(pChar, true);
	}
}

void CUnique::RemoveUnique(const std::string& key)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key or Dead: %s", key.c_str());
		return;
	}
	m_map_UniqueMob.erase(it);
	it->second->SetUnique(nullptr);
}

void CUnique::PurgeUnique(const std::string& key)
{
//	bool already_dead = false;
	if(IsUniqueDead(key))
	{
		sys_log(0, "PurgeUnique: Purging a dead unique!");
//		already_dead = true;
	}
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key or Dead: %s", key.c_str());
		return;
	}
	LPCHARACTER ch = it->second;
	m_map_UniqueMob.erase(it);
//	if(already_dead == false)
	if(ch)
		M2_DESTROY_CHARACTER(ch);
}

DWORD CUnique::GetUniqueVid(const std::string& key)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key or Dead: %s", key.c_str());
		return 0;
	}
	LPCHARACTER ch = it->second;
	return ch->GetVID();
}

bool CUnique::CheckUniqueExists(const std::string& key)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		return false;
	}
	return true;
}

float CUnique::GetUniqueHpPerc(const std::string& key)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);
	if (it == m_map_UniqueMob.end())
	{
		sys_err("Unknown Key : %s", key.c_str());
		return 0.0f;
	}
	return (100.f*it->second->GetHP())/it->second->GetMaxHP();
}

bool CUnique::IsUniqueDead(const std::string& key)
{
	TUniqueMobMap::iterator it = m_map_UniqueMob.find(key);

	if (it == m_map_UniqueMob.end())
	{
		return true;
	}

	return it->second->IsDead();
}

void CUnique::SpawnUnique(const char* key, DWORD vnum, const char* pos, LPCHARACTER pChar)
{
	if(pChar)
	{
		LPSECTREE_MAP pkSectreeMap = SECTREE_MANAGER::instance().GetMap(pChar->GetMapIndex());
		if (pkSectreeMap == NULL) {
			sys_err("CUnique: SECTREE_MAP not found for #%ld", pChar->GetMapIndex());
			return;
		}
		for (int i=0;i<100;i++)
		{
			int dx = number(pChar->GetX() - number(200, 750), pChar->GetX() + number(200, 750));
			int dy = number(pChar->GetY() - number(200, 750), pChar->GetY() + number(200, 750));
			int dir = number(0, 359);
			LPCHARACTER ch = CHARACTER_MANAGER::instance().SpawnMob(vnum, pChar->GetMapIndex(), dx, dy, 0, false, dir);

			if (ch)
			{
				m_map_UniqueMob.insert(make_pair(std::string(key), ch));
//				ch->SetDungeon(this);
				ch->SetUnique(this);
				break;
			}
			else
			{
				sys_err("Cannot spawn at %d %d", dx, dy);
			}
		}
	}
	else
	{
		sys_err("Cannot spawn with no character!!");
	}
}

void CUnique::SetUnique(const char* key, DWORD vid)
{
	LPCHARACTER ch = CHARACTER_MANAGER::instance().Find(vid);
	if (ch)
	{
		m_map_UniqueMob.insert(make_pair(std::string(key), ch));
		ch->SetUnique(this);
	}
}

void CUnique::Clear()
{
	for(TUniqueMobMap::iterator it = m_map_UniqueMob.begin(); it != m_map_UniqueMob.end(); it++) {
		m_map_UniqueMob.erase(it); //safely removing pointers without deleting
	}
}

CUniqueManager::CUniqueManager()
{
}

CUniqueManager::~CUniqueManager()
{
	m_map_pkUnique.clear();
}

LPUNIQUE CUniqueManager::Create(std::string id)
{
	sys_log(0,"M2_NEW CUnique attempt");

	itertype(m_map_pkUnique) it = m_map_pkUnique.find(id);
	if (it != m_map_pkUnique.end())
	{
		sys_err("M2_NEW CUnique already initialized!!! %s", id.c_str());
		return nullptr;
	}

	LPUNIQUE pUnique = M2_NEW CUnique(id);
	if (!pUnique)
	{
		sys_err("M2_NEW CUnique failed");
		return nullptr;
	}
	sys_log(0,"M2_NEW CUnique success!");
	m_map_pkUnique.insert(std::make_pair(id, pUnique));
	return pUnique;
}

LPUNIQUE CUniqueManager::Find(std::string id)
{
	if(m_map_pkUnique.empty())
	{
		sys_err("CUniqueManager::Find There is no Unique initialized!!");
		return nullptr;
	}

	itertype(m_map_pkUnique) it = m_map_pkUnique.find(id);
	if (it != m_map_pkUnique.end())
		return it->second;
	return nullptr;
}

void CUniqueManager::Remove(std::string id)
{
	if(m_map_pkUnique.empty())
	{
		sys_err("CUniqueManager::Find There is no Unique initialized!!");
		return;
	}

	itertype(m_map_pkUnique) it = m_map_pkUnique.find(id);
	if (it != m_map_pkUnique.end())
	{
		m_map_pkUnique.erase(it);
	}
}

void CUniqueManager::Clear()
{
	for(const auto& i : m_map_pkUnique)
	{
		i.second->Clear();
	}
}

std::vector<LPUNIQUE> CUniqueManager::GetUniqueList()
{
	std::vector<LPUNIQUE> result;
	for(const auto& i : m_map_pkUnique)
	{
		result.push_back(i.second);
	}
	return result;
}

