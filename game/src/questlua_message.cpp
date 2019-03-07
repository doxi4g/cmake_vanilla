#include "stdafx.h"
#include "constants.h"
#include "questmanager.h"
#include "questlua.h"
#include "char.h"
#include "party.h"
#include "buffer_manager.h"
#include "char_manager.h"
#include "packet.h"
#include "desc_client.h"
#include "desc_manager.h"
#include "item_manager.h"


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


namespace quest
{
	int message_send(lua_State* L)
	{
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("questlua_message::message_send: No Character in quest!!!");
			lua_pushnumber(L, 0);
			return 1;
		}

		unsigned long long fee = 0;
		//Check args
		if (!lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isstring(L, 3))
		{
			sys_err("questlua_message::message_send: You must provide a target, title and a message!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		std::string target = lua_tostring(L, 1);
		
		LPCHARACTER pTarget = CHARACTER_MANAGER::instance().FindPC(target.c_str());
		if(!pTarget)
		{
			sys_err("questlua_message::message_send: Target not found!");
			lua_pushnumber(L, 0);
			return 1;
		}
		
		std::string title = lua_tostring(L, 2);
		std::string message = lua_tostring(L, 3);
		if(title.length() > 48)
		{
			sys_err("CHARACTER::SendMessage: Title is over 32!!! Unable to save it.");
			lua_pushnumber(L, 0);
		}
		if(message.length() > 450) //we reserve the rest for id, from and itemlist
		{
			sys_err("CHARACTER::SendMessage: Message is over 450!!! Unable to save it.");
			lua_pushnumber(L, 0);
		}

		if(lua_isnumber(L, 4))
		{
			fee = lua_tonumber(L, 4);
		}
		
		//Extract the items
		std::vector<DWORD> items;
		int count = lua_gettop(L);
		if(count > 4)
		{
			//WE HAVE ITEMS YEAH
			for(int x = 5; x <= count; x++)
			{
				DWORD id = lua_tonumber(L, x);
				LPITEM item = ITEM_MANAGER::instance().Find(id);
				if(!item)
				{
					continue;
				}
				items.push_back(id);
			}
		}

		pTarget->RecvMessage(title, message, pChar, fee, items);
		lua_pushnumber(L, 1);
		return 1;
	}
	
	int message_count(lua_State* L)
	{
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("questlua_message::message_count: No Character in quest!!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		DWORD count = pChar->GetMessageCount();
		lua_pushnumber(L, count);
		
		return 1;
	}
	
	int message_read(lua_State* L)
	{
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("questlua_message::message_get_entry: No Character in quest!!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		
		DWORD id = 0;
		if(!lua_isnumber(L, 1))
		{
			sys_err(0, "questlua_message::message_get_entry: Cannot read message with no id!!!");
			lua_pushnumber(L, 0);
			id = lua_tonumber(L, 3);
		}

		TCharacterMessage* msg = pChar->ReadMessage(id);
		
		if(!msg)
		{
			lua_pushnumber(L, 0);
			return 1;
		}
		
		lua_newtable(L);
		lua_pushstring(L, "id");
		lua_pushnumber(L, id);
		lua_rawset(L, -3);
		lua_pushstring(L, "title");
		lua_pushstring(L, msg->title.c_str());
		lua_rawset(L, -3);
		lua_pushstring(L, "message");
		lua_pushstring(L, msg->message.c_str());
		lua_rawset(L, -3);
		lua_pushstring(L, "from");
		lua_pushstring(L, msg->from.c_str());
		lua_rawset(L, -3);
		lua_pushstring(L, "fee");
		lua_pushnumber(L, msg->fee);
		lua_rawset(L, -3);
		unsigned int count = 0;
		for(auto& x : msg->items)
		{
			std::string sindex = "item";
			sindex.append(std::to_string(count+1));
			lua_pushstring(L, sindex.c_str());
			lua_pushnumber(L, x);
			lua_rawset(L, -3);
			count++;
		}
		return 1;
	}

	int message_delete(lua_State* L)
	{
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("questlua_message::message_get_entry: No Character in quest!!!");
			lua_pushnumber(L, 0);
			return 1;
		}

		DWORD id = 0;
		if(!lua_isnumber(L, 1))
		{
			sys_err(0, "questlua_message::message_get_entry: Cannot read message with no id!!!");
			lua_pushnumber(L, 0);
			id = lua_tonumber(L, 3);
		}
		
		pChar->DeleteMessage(id);
		lua_pushnumber(L, 1);
		return 1;
	}
	
	int message_clear_all(lua_State* L)
	{
		const LPCHARACTER pChar = CQuestManager::instance().GetCurrentCharacterPtr();
		if(!pChar)
		{
			sys_err("questlua_message::message_get_entry: No Character in quest!!!");
			lua_pushnumber(L, 0);
			return 1;
		}
		pChar->ClearMessageList();
		lua_pushnumber(L, 1);
		return 1;
	}

	void RegisterMessageFunctionTable() 
	{
		luaL_Reg message_functions[] = 
		{
			{ "send",		message_send	},
			{ "count",		message_count	},
			{ "read",		message_read	},
			{ "delete",		message_delete	},
			{ "clear_all",		message_clear_all	},

			{ NULL,				NULL			}
		};
		CQuestManager::instance().AddLuaFunctionTable("message", message_functions);
	}
}
