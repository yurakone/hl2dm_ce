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