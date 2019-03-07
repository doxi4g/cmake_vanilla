
#include "stdafx.h"

#include "config.h"
#include "char.h"
#include "char_manager.h"
#include "affect.h"
#include "packet.h"
#include "buffer_manager.h"
#include "desc_client.h"
#include "battle.h"
#include "guild.h"
#include "utils.h"
#include "locale_service.h"
#include "lua_incl.h"
#include "arena.h"
#include "horsename_manager.h"
#include "item.h"
#include "item_manager.h"
#include "questmanager.h"
#include "questlua.h"

#include <sstream>


std::vector<std::string> &string_split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> string_split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    string_split(s, delim, elems);
    return elems;
}

//Sends a message to the character
void CHARACTER::RecvMessage(std::string title, std::string msg, LPCHARACTER from, unsigned long long fee, std::vector<DWORD> items)
{
	if(title.length() > 48)
	{
		sys_err("CHARACTER::SendMessage: Title is over 32!!! Unable to save it.");
	}
	if(msg.length() > 450) //we reserve the rest for id, from and itemlist
	{
		sys_err("CHARACTER::SendMessage: Message is over 450!!! Unable to save it.");
	}
	//message struct
	TCharacterMessage* message = new TCharacterMessage;
	message->title = title;
	message->message = msg;
	message->from = from->GetName();
	message->fee = fee;
	for(auto& item : items)
	{
		message->items.push_back(item);
	}
	
	//item void
	unsigned int idx = 0;
	for(const DWORD& id : items)
	{
		LPITEM item = ITEM_MANAGER::instance().Find(id);
		//make sure item is not a nullptr
		if(nullptr == item)
		{
			items.erase(items.begin() + idx);
			continue;
		}

		if(item->IsEquipped())
		{
			items.erase(items.begin() + idx);
			continue;
		}
		//Void item!
		item->MoveToVoid();
	}

	//Insert message into storage
	m_messages.push_back(message);
	
	//Trigger quest event_callback
	quest::CQuestManager::instance().Message(GetPlayerID(), from->GetPlayerID());
}

TCharacterMessage* CHARACTER::ReadMessage(DWORD id)
{
	if(id > m_messages.size())
	{
		return nullptr;
	}
	return m_messages.at(id);
}

void CHARACTER::SaveMessages()
{
	std::string msgdir = "share/messages/";
	msgdir.append(GetName());
	if(m_messages.size() == 0)
	{
		std::remove(msgdir.c_str());
		return;
	}
	FILE* stream = fopen(msgdir.c_str(), "w+");
	for(const auto &i : m_messages)
	{
		std::string line = i->title;
		line.append("|");
		line.append(i->message);
		line.append("|");
		line.append(i->from);
		line.append("|");
		line.append(std::to_string(i->fee));
		line.append("|");
		if(i->items.size() > 0)
		{
			for(unsigned int k = 0; k < i->items.size(); k++)
			{
				line.append(std::to_string(i->items.at(k)));
				if(k < i->items.size() - 1)
				{
					line.append("|");
				}
			}
		}
		line.append("\n");
		fwrite(line.c_str(), sizeof(char), sizeof(line), stream);
	}
}

bool CHARACTER::ReloadMessages()
{
	m_messages.clear();
	std::string msgdir = "share/messages/";
	msgdir.append(GetName());
	FILE* stream = fopen(msgdir.c_str(), "r");
	if(!stream)
	{
		sys_log(0, "No messages for character %s", GetName());
		return false;
	}
	char line[512];
	while(fgets(line, sizeof(line), stream))
	{
		if(line[0] == '\n')
			continue;

		std::string line2 = line;
		std::vector<std::string> splitted = string_split(line2, '|');
		TCharacterMessage* message = new TCharacterMessage;
		message->title = splitted[0];
		message->message = splitted[1];
		message->from = splitted[2];
		message->fee = atoi(splitted[3].c_str());
		DWORD count = 0;
		std::vector<DWORD> items;
		for(const auto& x : splitted)
		{
			count++;
			if(count <= 3)
				continue;
			message->items.push_back(atoi(x.c_str()));
		}
		m_messages.push_back(message);
	}
	return true;
}

void CHARACTER::ClearMessageList()
{
	m_messages.clear();
	SaveMessages();
}

bool CHARACTER::DeleteMessage(DWORD id)
{
	if(id > m_messages.size())
	{
		return false;
	}
	m_messages.erase(m_messages.begin() + id - 1);
	return true;
}

