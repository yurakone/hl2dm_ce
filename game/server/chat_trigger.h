#ifndef CHAT_TRIGGER_H
#define CHAT_TRIGGER_H

#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"

class CHL2MP_Chat
{
public:
	static void CheckChatText(char* p, int bufsize);
	static void LoadChatCommands();
	static bool HandleTeamCommand(const char* command, CBasePlayer* pPlayer);
	static bool ProcessChatCommand(const char* command, const char* args, CBasePlayer* pPlayer);
};

extern CHL2MP_Chat* g_pHL2MPChat;

inline CHL2MP_Chat* HL2MPChat()
{
	return static_cast<CHL2MP_Chat*>(g_pHL2MPChat);
}

// Console command to reload chat commands
void CC_ReloadChatCommands();

#endif // CHAT_TRIGGER_H
