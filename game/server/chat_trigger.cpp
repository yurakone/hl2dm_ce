//-----------------------------------------------------------------------------
// Purpose: Checks chat for certain strings (chat commands) with config support
//-----------------------------------------------------------------------------
#include "cbase.h"
#include "chat_trigger.h"
#include "hl2mp/hl2mp_player.h"
#include "admin/hl2mp_serveradmin.h"
#include "filesystem.h"
#include "utlvector.h"
#include "motd_menu.cpp"
#include "tier0/memdbgon.h"

bool g_bAdminSystem = false;

// Structure to hold chat command data
struct ChatCommand_t
{
	char trigger[64];           // Command trigger (e.g., "rtv", "!ban")
	char consoleCmd[256];       // Console command to execute
	bool requiresArgs;          // Does this command need arguments?
	bool printToConsole;        // Should we print "check console" message?
	bool echoToChat;            // Should we return console output to chat?
	bool teamplayOnly;          // Only works in teamplay mode?
	int teamRestriction;        // 0 = no restriction, 1 = spectator only, 2 = team only, etc.
	int maxEchoLines;           // Maximum lines to echo back (0 = unlimited)
	char echoMessage[256];      // Custom message to echo instead of console output
};

// Storage for loaded commands
CUtlVector<ChatCommand_t> g_ChatCommands;

//-----------------------------------------------------------------------------
// Purpose: Load chat commands from config file
//-----------------------------------------------------------------------------
void CHL2MP_Chat::LoadChatCommands()
{
	g_ChatCommands.Purge();

	KeyValues* kv = new KeyValues("ChatCommands");
	if (!kv->LoadFromFile(filesystem, "cfg/admin/chat_commands.cfg", "MOD"))
	{
		Warning("Could not load cfg/admin/chat_commands.cfg\n");
		kv->deleteThis();
		return;
	}

	// Iterate through all command sections
	for (KeyValues* pCommand = kv->GetFirstSubKey(); pCommand; pCommand = pCommand->GetNextKey())
	{
		ChatCommand_t cmd;
		memset(&cmd, 0, sizeof(cmd));

		// Get command properties
		Q_strncpy(cmd.trigger, pCommand->GetName(), sizeof(cmd.trigger));
		Q_strncpy(cmd.consoleCmd, pCommand->GetString("console_cmd", ""), sizeof(cmd.consoleCmd));
		cmd.requiresArgs = pCommand->GetBool("requires_args", false);
		cmd.printToConsole = pCommand->GetBool("print_to_console", false);
		cmd.echoToChat = pCommand->GetBool("echo_to_chat", false);
		cmd.maxEchoLines = pCommand->GetInt("max_echo_lines", 5);
		cmd.teamplayOnly = pCommand->GetBool("teamplay_only", false);
		cmd.teamRestriction = pCommand->GetInt("team_restriction", 0);
		Q_strncpy(cmd.echoMessage, pCommand->GetString("echo_message", ""), sizeof(cmd.echoMessage));

		// Add to our list
		g_ChatCommands.AddToTail(cmd);
	}

	kv->deleteThis();
	Msg("Loaded %d chat commands from config\n", g_ChatCommands.Count());
}

//-----------------------------------------------------------------------------
// Purpose: Handle special team commands
//-----------------------------------------------------------------------------
bool CHL2MP_Chat::HandleTeamCommand(const char* command, CBasePlayer* pPlayer)
{
	if (Q_strcmp(command, "!1") == 0 || Q_strcmp(command, "/1") == 0)
	{
		if (!pPlayer->IsObserver())
		{
			engine->ClientCommand(pPlayer->edict(), "jointeam 1");
			if (!GameRules()->IsTeamplay())
			{
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You are in spectator mode. Type !2 to join the game\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You are in spectator mode. Type !2 to join BLUE team or !3 to the RED team\n");
			}
		}
		else
		{
			if (!GameRules()->IsTeamplay())
			{
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You already in spectator mode. Type !2 to join the game\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You already in spectator mode. Type !2 to join BLUE team or !3 to the RED team\n");
			}
		}
		return true;
	}
	else if (Q_strcmp(command, "!2") == 0 || Q_strcmp(command, "/2") == 0)
	{
		if (GameRules()->IsTeamplay())
		{
			if (pPlayer->IsObserver() || pPlayer->GetTeamNumber() != 2)
			{
				engine->ClientCommand(pPlayer->edict(), "jointeam 2");
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You have joined the BLUE team\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, "\a305CDE" "You already in BLUE team.Type\aFF0000 !3\a305CDE to join\aFF0000 RED\a305CDE team or \a898989 !1\a305CDE to\a898989 spectate\n");
			}
		}
		else
		{
			if (pPlayer->IsObserver())
			{
				engine->ClientCommand(pPlayer->edict(), "jointeam 2");
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You have joined the game\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, "\a6D8196" "You already in game. Type\a898989 !1\a6D8196 to\a898989 spectate\n");
			}
		}
		return true;
	}
	else if (Q_strcmp(command, "!3") == 0 || Q_strcmp(command, "/3") == 0)
	{
		if (GameRules()->IsTeamplay())
		{
			if (pPlayer->IsObserver() || pPlayer->GetTeamNumber() != 3)
			{
				engine->ClientCommand(pPlayer->edict(), "jointeam 3");
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You have joined the RED team\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, "\x07""FF0000" "You already in RED team.Type\a305CDE !2\aFF0000 to join\a305CDE BLUE\aFF0000 team or\a898989 !1\aFF0000 to\a898989 spectate\n");
			}
		}
		else
		{
			if (pPlayer->IsObserver())
			{
				engine->ClientCommand(pPlayer->edict(), "jointeam 3");
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "You have joined the game\n");
			}
			else
			{
				UTIL_PrintToClient(pPlayer, "\a6D8196" "You already in game. Type\a898989 !1\a6D8196 to\a898989 spectate\n");
			}
		}
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Process chat command using config data
//-----------------------------------------------------------------------------
bool CHL2MP_Chat::ProcessChatCommand(const char* command, const char* args, CBasePlayer* pPlayer)
{
	for (int i = 0; i < g_ChatCommands.Count(); i++)
	{
		const ChatCommand_t& cmd = g_ChatCommands[i];

		// Check if this command matches our trigger
		if (Q_strcmp(command, cmd.trigger) == 0)
		{
			// Check teamplay restriction
			if (cmd.teamplayOnly && !GameRules()->IsTeamplay())
				continue;

			// Check team restriction
			if (cmd.teamRestriction != 0)
			{
				int playerTeam = pPlayer->GetTeamNumber();
				if (cmd.teamRestriction == 1 && !pPlayer->IsObserver()) // Spectator only
					continue;
				if (cmd.teamRestriction == 2 && pPlayer->IsObserver()) // Team only
					continue;
				if (cmd.teamRestriction > 2 && playerTeam != cmd.teamRestriction) // Specific team
					continue;
			}

			char finalCmd[512];

			// Build the final console command
			if (cmd.requiresArgs && args && args[0] != '\0')
			{
				Q_snprintf(finalCmd, sizeof(finalCmd), "%s %s", cmd.consoleCmd, args);
			}
			else if (!cmd.requiresArgs)
			{
				Q_snprintf(finalCmd, sizeof(finalCmd), "%s", cmd.consoleCmd);
			}
			else
			{
				// Command requires args but none provided
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "This command requires arguments\n");
				return true;
			}

			// Execute the command
			engine->ClientCommand(pPlayer->edict(), finalCmd);

			// Handle echo to chat
			if (cmd.echoToChat && cmd.echoMessage[0] != '\0')
			{
				// Use custom echo message
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "%s\n", cmd.echoMessage);
			}

			// Print console message if needed
			if (cmd.printToConsole)
			{
				UTIL_PrintToClient(pPlayer, CHAT_ADMIN "Check your console for output.\n");
			}

			return true;
		}
	}

	return false;
}

void CHL2MP_Chat::CheckChatText(char* p, int bufsize)
{
	if (!g_bAdminSystem)
		return;

	CBasePlayer* pPlayer = UTIL_GetCommandClient();

	if (!p || bufsize <= 0 || !pPlayer)
		return;

	// Load commands on first use or if we have no commands loaded
	if (g_ChatCommands.Count() == 0)
	{
		LoadChatCommands();
	}

	// Handle special hardcoded commands first (rtv, nominate)
	if ((Q_strcmp(p, "rtv") == 0) || (Q_strcmp(p, "!rtv") == 0) || (Q_strcmp(p, "rockthevote") == 0))
	{
		engine->ClientCommand(pPlayer->edict(), "rtv");
		return;
	}

	if ((Q_strcmp(p, "nominate") == 0) || (Q_strcmp(p, "!nominate") == 0))
	{
		engine->ClientCommand(pPlayer->edict(), "nominate");
		return;
	}

	if ((Q_strcmp(p, "tmotd") == 0) || (Q_strcmp(p, "!tmotd") == 0))
	{
		ShowCustomMOTD(static_cast<CHL2MP_Player*>(pPlayer));
		return;
	}
	// Handle team commands
	if (HandleTeamCommand(p, pPlayer))
		return;

	// Process chat commands that start with ! or /
	if (p[0] == '!' || p[0] == '/')
	{
		char command[64];
		const char* args = NULL;

		// Find the first space to separate command from arguments
		char* spacePos = Q_strstr(p, " ");
		if (spacePos)
		{
			// Extract command part
			int cmdLen = spacePos - p;
			if (cmdLen >= sizeof(command))
				cmdLen = sizeof(command) - 1;

			Q_strncpy(command, p, cmdLen + 1);
			command[cmdLen] = '\0';

			// Skip the space for arguments
			args = spacePos + 1;
		}
		else
		{
			// No arguments, just copy the whole thing
			Q_strncpy(command, p, sizeof(command));
		}

		// Try to process the command using our config
		if (ProcessChatCommand(command, args, pPlayer))
			return;
	}
}