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

//Noblock
ConVar mp_noblock(
	"mp_noblock",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, disable collisions between players");
//Specpanel
ConVar sv_specpanel_disable(
	"sv_specpanel_disable",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, force hide specpanel");
//Fastgather
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
//Suivoice
ConVar mp_suitvoice(
	"mp_suitvoice",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, game will enable suit notifications");
//Lockteams
ConVar mp_lockteams(
	"mp_lockteams",
	"0",
	FCVAR_GAMEDLL | FCVAR_NOTIFY,
	"If non-zero, teams will be locked, new players will move to spectators");
//Armorsparks
ConVar mp_armor_sparks(
	"mp_armor_sparks",
	"0",
	FCVAR_GAMEDLL,
	"If non-zero, game will enable spark effect if suit get damage");

ConVar mp_kevlar_sound_enabled(
	"mp_kevlar_sound_enabled",
	"1",
	FCVAR_GAMEDLL,
	"If non-zero, game will enable sound effect if suit get damage");

//Spec on connect
ConVar sv_join_spec_on_connect(
	"sv_join_spec_on_connect",
	"0",
	0,
	"If non-zero, put connecting players to team spectators on fully joined");

//Freeze players
ConVar mp_freeze_players(
	"mp_freeze_players",
	"0",
	0,
	"If non-zero, freeze players");

//Server downloadable files
ConVar mp_server_files(
	"mp_server_files",
	"1",
	FCVAR_GAMEDLL ,
	"If non-zero, allow clients to download custom files from server");

//Armor effects file
ConVar mp_armor_effects(
	"mp_armor_effects",
	"blood_impact_synth_01",
	FCVAR_GAMEDLL,
	"Particle system name for armor impact effects");

//Impact armor effects file
ConVar mp_helmet_effects(
	"mp_helmet_effects",
	"blood_spurt_synth_01b",
	FCVAR_GAMEDLL,
	"Particle system name for helmet impact effects");

//Helmet sound
ConVar mp_helmetsound_enabled(
	"mp_helmetsound_enabled",
	"1",
	FCVAR_GAMEDLL ,
	"If non-zero, play a sound when helmet blocks a headshot");

//Hitsounds projectiles
ConVar mp_hitsounds_projectiles(
	"mp_hitsounds_projectiles",
	"1",
	FCVAR_GAMEDLL ,
	"If non-zero, play hitsounds for projectile weapons");

//Armor impact volume
ConVar mp_armor_impact_volume(
	"mp_armor_impact_volume",
	"0.5",
	FCVAR_GAMEDLL,
	"Volume of armor impact effect, 0.0 - 1.0, def 0.5");
//ShotGun pump
ConVar sv_shotgun_pump(
	"sv_shotgun_pump",
	"1",
	0,
	"Defines the shotgun pump when deploying the shotgun, 1 - Default, 2 - No pump, 3 - Always pump");
//ShotgunCone
ConVar sv_shotgun_cone(
	"sv_shotgun_cone",
	"1", 
	0,
	"Defines the shotgun pellets spread cone, 1 - Default 10 degrees, 0 - Wide 15 degrees");