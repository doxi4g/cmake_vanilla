#include "stdafx.h"
#include "constants.h"
#include "questmanager.h"
#include "questlua.h"
//#include "dungeon.h"
//#include "unique.h"
#include "char.h"
#include "party.h"
#include "buffer_manager.h"
#include "char_manager.h"
#include "packet.h"
#include "desc_client.h"
#include "desc_manager.h"


#undef sys_err
#ifndef __WIN32__
#define sys_err(fmt, args...) quest::CQuestManager::instance().QuestError(__FUNCTION__, __LINE__, fmt, ##args)
#else
#define sys_err(fmt, ...) quest::CQuestManager::instance().QuestError(__FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#endif

//extern CUnique 

//template <class Func> Func CUnique::ForEachMember(Func f)
//{
//	itertype(m_set_pkCharacter) it;
//
//	for (it = m_set_pkCharacter.begin(); it != m_set_pkCharacter.end(); ++it)
//	{
//		sys_log(0, "Unique ForEachMember %s", (*it)->GetName());
//		f(*it);
//	}
//	return f;
//}

CUniqueManager* pUniqueManager = nullptr;
LPUNIQUE master = nullptr;
LPUNIQUE character = nullptr;


namespace quest
{
	void setup()
	{
		pUniqueManager = CQuestManager::instance().pUniqueManager;
		master = CQuestManager::instance().master;
		character = CQuestManager::instance().character;
	}
	int unique_init(lua_State* L)
	{
		sys_log(0, "Warning! Using init is deprecated!");
		pUniqueManager = new CUniqueManager();
		master = pUniqueManager->Create("__DEFAULT__");
		character = pUniqueManager->Create("__CHARACTER__");
		return 0;
	}
	int unique_spawn_unique(lua_State* L)
	{
		if (!lua_isstring(L,1) || !lua_isnumber(L,2) || !lua_isstring(L,3))
			return 0;
		sys_log(0,"QUEST_unique_SPAWN_UNIQUE %s %d %s", lua_tostring(L,1), (int)lua_tonumber(L,2), lua_tostring(L,3));
		
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		LPUNIQUE worker = master;
		if(lua_isstring(L,4))
		{
			std::string key = lua_tostring(L, 4);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::spawn_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		if(worker->CheckUniqueExists(lua_tostring(L,1))== true)
		{
			sys_log(0, "Unique already exists! %s Gonna purge..", lua_tostring(L, 1));
			worker->PurgeUnique(lua_tostring(L, 1));
		}
		worker->SpawnUnique(lua_tostring(L,1), (DWORD)lua_tonumber(L,2), lua_tostring(L,3), pChar);

		return 0;
	}

	int unique_set_unique(lua_State* L)
	{
		if (!lua_isstring(L, 1) || !lua_isnumber(L, 2))
			return 0;
		sys_log(0, "Starting the procedure to set unique!!");
		DWORD vid = (DWORD) lua_tonumber(L, 2);
//		CUniqueManager* pUniqueManager = new CUniqueManager();
//		LPUNIQUE pUnique = pUniqueManager->Find(1);
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		LPCHARACTER ch = CHARACTER_MANAGER::instance().Find(vid);
		if (ch && ch->IsPC())
		{
			worker = character;
		}
		if(lua_isstring(L,3))
		{
			std::string key = lua_tostring(L, 3);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		if(worker->CheckUniqueExists(lua_tostring(L,1))== true)
		{
			sys_log(0, "Unique already exists! %s Gonna purge..", lua_tostring(L, 1));
			worker->PurgeUnique(lua_tostring(L, 1));
		}
		worker->SetUnique(lua_tostring(L, 1), vid);
		sys_log(0, "Unique set succesful!");
		return 0;
	}
	
	int unique_get_container_list(lua_State* L)
	{
		if(!pUniqueManager)
		{
			sys_err("Unique_get_container: Unique is not initialized!");
			return 1;
		}
		std::vector<LPUNIQUE> vUniqueList = pUniqueManager->GetUniqueList();
		lua_newtable(L);
		for(const auto& unique : vUniqueList)
		{
			lua_pushstring(L, unique->GetID().c_str());
			lua_rawset(L, -2);
		}
		return 0;
	}

	int unique_get_container_vid_list(lua_State* L)
	{
		std::string key = "";
		if (lua_isstring(L,1))
		{
			key = lua_tostring(L,1);
			return 1;
		}

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = pUniqueManager->Find(key);
		if(!worker)
		{
			sys_err("Could not find proper Unique!!!");
			return 1;
		}
		lua_newtable(L);
		
		std::vector<DWORD> vidtable = worker->MassGetUniqueVID();
		for(const auto& unique : vidtable)
		{
			std::string vid = std::to_string(unique);
			lua_pushstring(L, vid.c_str());
			lua_rawset(L, -2);
		}
		return 0;
	}

	int unique_delete_container(lua_State* L)
	{
		std::string key = "";
		if (lua_isstring(L,1))
		{
			key = lua_tostring(L,1);
			return 1;
		}
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(key.compare("__CHARACTER__") == 0 || key.compare("__DEFAULT__") == 0)
		{
			sys_err("Cannot cast delete on standard unique-container! Flushing instead!!!");
			
			LPUNIQUE worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("Could not find standard Unique container!!!");
				return 1;
			}
			worker->Clear();
		}
		pUniqueManager->Remove(key);
		return 0;
	}

	int unique_get_vid(lua_State* L)
	{
		if (!lua_isstring(L,1))
		{
			lua_pushnumber(L,0);
			return 1;
		}

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		
		lua_pushnumber(L, worker->GetUniqueVid(lua_tostring(L,1)));
		return 0;
	}

	int unique_check_exists(lua_State* L)
	{
		if (!lua_isstring(L,1))
		{
			sys_err("unique_check_exists: String expected. Not provided.");
			lua_pushnumber(L,0);
			return 1;
		}
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		if(worker->CheckUniqueExists(lua_tostring(L,1))== true)
		{
			lua_pushboolean(L,true);
			return 1;
		}
		sys_log(0, "unique_check_exists: Unique mob not found %s!!", lua_tostring(L,1));
		lua_pushboolean(L,false);
		return 0;
	}

	int unique_set_maxhp(lua_State* L)
	{
		if (!lua_isstring(L,1) || !lua_isnumber(L,2))
			return 0;

//		CQuestManager& q = CQuestManager::instance();
//		CUniqueManager* pUniqueManager = new CUniqueManager();
//		LPUNIQUE pUnique = pUniqueManager->Find(1);
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		worker->UniqueSetMaxHP(lua_tostring(L,1), (int)lua_tonumber(L,2));

		return 0;
	}

	int unique_set_hp(lua_State* L)
	{
		if (!lua_isstring(L,1) || !lua_isnumber(L,2))
			return 0;

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,3))
		{
			std::string key = lua_tostring(L, 3);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		worker->UniqueSetHP(lua_tostring(L,1), (int)lua_tonumber(L,2));

		return 0;
	}

	int unique_set_def_grade(lua_State* L)
	{
		if (!lua_isstring(L,1) || !lua_isnumber(L,2))
			return 0;


		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,3))
		{
			std::string key = lua_tostring(L, 3);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		worker->UniqueSetDefGrade(lua_tostring(L,1), (int)lua_tonumber(L,2));

		return 0;
	}

	int unique_get_hp_perc(lua_State* L)
	{
		if (!lua_isstring(L,1))
		{
			lua_pushnumber(L,0);
			return 1;
		}

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}

		lua_pushnumber(L, worker->GetUniqueHpPerc(lua_tostring(L,1)));
		return 0;
	}

	int unique_is_dead(lua_State* L)
	{
		if (!lua_isstring(L,1))
		{
			lua_pushboolean(L, 0);
			return 1;
		}

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}
		lua_pushboolean(L, master->IsUniqueDead(lua_tostring(L,1))?1:0);
		return 0;
	}

	int unique_kill(lua_State* L)
	{
		if (!lua_isstring(L,1))
			return 0;
		sys_log(0,"QUEST_DUNGEON_KILL_UNIQUE %s", lua_tostring(L,1));

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("CUnique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}

		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("Attempt to kill unique monster without char!? Cowardly refusing..");
			return 0;
		}
		worker->KillUnique(lua_tostring(L,1), pChar);

		return 0;
	}

	int unique_purge(lua_State* L)
	{
		if (!lua_isstring(L,1))
			return 0;
		sys_log(0,"QUEST_DUNGEON_PURGE_UNIQUE %s", lua_tostring(L,1));

		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			return 1;
		}
		LPUNIQUE worker = master;
		if(lua_isstring(L,2))
		{
			std::string key = lua_tostring(L, 2);
			worker = pUniqueManager->Find(key);
			if(!worker)
			{
				sys_err("questlua_unique::set_unique: Could not find unique-container by key! %s", key.c_str());
				return 1;
			}
		}

		worker->PurgeUnique(lua_tostring(L,1));

		return 0;
	}
	
	int unique_walk_to_pos(lua_State* L)
	{
		if(!lua_isstring(L, 1))
		{
			sys_err("questlua_unique::unique_walk_to_pos: Args expected: key(string), x(int), y(int)[, container(string)]!");
			lua_pushnumber(L, 0);
			return 0;
		}
		if (!lua_isnumber(L,2) || !lua_isnumber(L, 3))
		{
			sys_err("questlua_unique::unique_walk_to_pos: You need to provide a valid x and y!");
			lua_pushnumber(L, 0);
			return 0;
		}
		if(!pUniqueManager)
		{
			sys_err("Unique_Manager is not initialized!!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		if(!master)
		{
			sys_err("Unique default is not initialized!!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		std::string key = lua_tostring(L, 1);
		long x = lua_tonumber(L, 2);
		long y = lua_tonumber(L, 3);
		LPUNIQUE worker = master;
		if(lua_isstring(L,4))
		{
			std::string kcontainer = lua_tostring(L, 4);
			worker = pUniqueManager->Find(kcontainer);
			if(!worker)
			{
				sys_err("questlua_unique::unique_walk_to_pos: Could not find unique-container by key! %s", kcontainer.c_str());
			lua_pushnumber(L, 0);
				return 1;
			}
		}
		worker->UniqueMoveToPos(key, x, y);
		lua_pushnumber(L, 1);
		return 0;
	}

	void RegisterUniqueFunctionTable() 
	{
		luaL_Reg unique_functions[] = 
		{
			{ "spawn_unique",		unique_spawn_unique	},
			{ "set_unique",			unique_set_unique	},
			{ "purge_unique",		unique_purge	},
			{ "kill_unique",		unique_kill	},
			{ "is_unique_dead",		unique_is_dead	},
			{ "get_hp_perc",		unique_get_hp_perc},
			{ "set_def_grade",	unique_set_def_grade},
			{ "set_hp",		unique_set_hp	},
			{ "set_maxhp",		unique_set_maxhp},
			{ "get_vid",		unique_get_vid},
			{ "exists",		unique_check_exists},
			{ "get_container_list",		unique_get_container_list},
			{ "get_container_vid_list",		unique_get_container_vid_list},
			{ "delete_container",		unique_delete_container},
			{ "walk_to_pos",		unique_walk_to_pos},
			{ "init",		unique_init},

			{ NULL,				NULL			}
		};
		CQuestManager::instance().AddLuaFunctionTable("unique", unique_functions);
		setup();
	}
}
