//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose:  
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hl2mp_cvars.h"



// Ready restart
ConVar mp_readyrestart(
							"mp_readyrestart", 
							"0", 
							FCVAR_GAMEDLL,
							"If non-zero, game will restart once each player gives the ready signal" );

// Ready signal
ConVar mp_ready_signal(
							"mp_ready_signal",
							"ready",
							FCVAR_GAMEDLL,
							"Text that each player must speak for the match to begin" );
// Ear ringing
ConVar mp_ear_ringing(
	"mp_ear_ringing",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, produce ringing sound caused by explosion/blast damage");

// red screen
ConVar mp_redscreen(
	"mp_redscreen",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, draws redscreen caused by high damage");

// playermodel message
ConVar sv_showplayermodel(
	"sv_showplayermodel",
	"1", 
	FCVAR_GAMEDLL,
	"If non-zero, shows the updated player model name to the player");

//Game Description
ConVar sv_gamedesc(
	"sv_gamedesc",
	"",
	FCVAR_GAMEDLL,
	"Shows custom game description");

//Allow teamplay live change
ConVar sv_instant_teamplay(
	"sv_instant_teamplay",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, allow live change of teamplay");

//noblock
ConVar mp_noblock(
	"mp_noblock",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, disable collisions between players");
//specpanel
ConVar sv_specpanel_disable(
	"sv_specpanel_disable",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, force hide specpanel");
//fastgather
ConVar mp_fast_gather(
	"mp_fast_gather",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"Gathering physgun mode, 0 - Disabled, 1 - Fast Gather, 2 - Vacuum mode");
//killsounds
ConVar mp_killsounds_enabled(
	"mp_killsounds_enabled",
	"1",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"Killsounds, 0 - Disabled, 1 - Enable");
//Hitsounds
ConVar mp_hitsounds_enabled(
	"mp_hitsounds_enabled",
	"1",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"Hitsounds, 0 - Disabled, 1 - Enable");
//suivoice
ConVar mp_suitvoice(
	"mp_suitvoice",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, game will enable suit notifications");
//lockteams
ConVar mp_lockteams(
	"mp_lockteams",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, teams will be locked, new players will move to spectators");

ConVar mp_armor_sparks(
	"mp_armor_sparks",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, game will enable spark effect if suit get damage");
