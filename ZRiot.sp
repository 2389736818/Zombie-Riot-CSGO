#pragma semicolon 1
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>
#include <cstrike>

#undef REQUIRE_PLUGIN
#include <market>

// Include Parts
#include "zriot/zombieriot"
#include "zriot/global"
#include "zriot/cvars"
#include "zriot/translation"
#include "zriot/offsets"
#include "zriot/ambience"
#include "zriot/zombiedata"
#include "zriot/daydata"
#include "zriot/targeting"
#include "zriot/overlays"
#include "zriot/zombie"
#include "zriot/hud"
#include "zriot/sayhooks"
#include "zriot/teamcontrol"
#include "zriot/weaponrestrict"
#include "zriot/commands"
#include "zriot/event"
#include "zriot/armor"
#include "zriot/cooldown"
#include "zriot/zombienames"
#include "zriot/buyzone"
#include "zriot/servercommands"

// Version Information
#define VERSION "0.1"
public Plugin:myinfo =
{
    name = "Zombie Riot CS:GO", 
    author = "TummieTum - Greyscale", 
    description = "Kill the zombies!", 
    version = VERSION, 
    url = "Team-Secretforce.com"
};

public APLRes:AskPluginLoad2(Handle:myself, bool:late, String:error[], err_max)
{
    CreateGlobals();
    return APLRes_Success;
}

public OnPluginStart()
{
    LoadTranslations("common.phrases.txt");
    LoadTranslations("zombieriot.phrases.txt");
    
    // ======================================================================
    
    ZRiot_PrintToServer("Plugin loading");
    
    // ======================================================================
    
    ServerCommand("bot_kick");
    
    // ======================================================================
    
    HookEvents();
    HookChatCmds();
    CreateCvars();
    HookCvars();
    CreateCommands();
    FindOffsets();
    InitTeamControl();
    InitWeaponRestrict();
    Cooldown_Map();
    Zombienames_Default();
    
    // ======================================================================
    
    trieDeaths = CreateTrie();
    
    // ======================================================================
    
    market = LibraryExists("market");
    
    // ======================================================================
    
    ZRiot_PrintToServer("Plugin loaded");
}

public OnPluginEnd()
{
    ZRiotEnd();
}

public OnLibraryRemoved(const String:name[])
{
	if (StrEqual(name, "market"))
	{
		market = false;
	}
}
 
public OnLibraryAdded(const String:name[])
{
	if (StrEqual(name, "market"))
	{
		market = true;
	}
}

public OnMapStart()
{
    MapChangeCleanup();
    
    LoadModelData();
    LoadDownloadData();
    
    BuildPath(Path_SM, gMapConfig, sizeof(gMapConfig), "configs/zriot");
    
    LoadZombieData(true);
    LoadDayDataDif1(true);
    LoadDayDataDif2(true);
    LoadDayDataDif3(true);
    
    FindMapSky();
    CheckMapConfig();
	
    // Custom TumTum
    ReloadNames();
    GenerateRedirects();
    Cooldown_Start();
    Market_Load();
    RemoveBuyZone();
}

public OnConfigsExecuted()
{
    UpdateTeams();
    Servercommands_configs();
    
    FindHostname();
    
    LoadAmbienceData();
    
    decl String:mapconfig[PLATFORM_MAX_PATH];
    
    GetCurrentMap(mapconfig, sizeof(mapconfig));
    Format(mapconfig, sizeof(mapconfig), "sourcemod/zriot/%s.cfg", mapconfig);
    
    decl String:path[PLATFORM_MAX_PATH];
    Format(path, sizeof(path), "cfg/%s", mapconfig);
    
    if (FileExists(path))
    {
        ServerCommand("exec %s", mapconfig);
    }
}

public OnClientPutInServer(client)
{
    new bool:fakeclient = IsFakeClient(client);
    
    InitClientDeathCount(client);
    
    new deathcount = GetClientDeathCount(client);
    new deaths_before_zombie = GetDayDeathsBeforeZombie(gDay);
    
    bZombie[client] = !fakeclient ? ((deaths_before_zombie > 0) && (fakeclient || (deathcount >= deaths_before_zombie))) : true;
    
    gZombieID[client] = -1;
    
    gTarget[client] = -1;
    RemoveTargeters(client);
    
    tRespawn[client] = INVALID_HANDLE;
    
    ClientHookUse(client);
    
    FindClientDXLevel(client);
	
    Cooldown_On(client);
}

public OnClientDisconnect(client)
{
    if (!IsPlayerHuman(client))
        return;
    
    new count;
    
    new maxplayers = GetMaxClients();
    for (new x = 1; x <= maxplayers; x++)
    {
        if (!IsClientInGame(x) || !IsPlayerHuman(x) || GetClientTeam(x) <= CS_TEAM_SPECTATOR)
            continue;
        
        count++;
    }
    
    if (count <= 1 && tHUD != INVALID_HANDLE)
    {
        CS_TerminateRound(5.0, CSRoundEnd_GameStart);
    }
}

// Create Spawntimer + Armor / Helmet
public Event_PlayerSpawn(Handle:event, const String:name[], bool:dontBroadcast)
{
	CreateTimer(0.1, Event_HandleSpawn, GetEventInt(event, "userid"));
}

// Show Items on Spawn
public Action:Event_HandleSpawn(Handle:timer, any:user_index)
{
    new client_index = GetClientOfUserId(user_index);
    if (!client_index)
    return;
	
    if (!IsPlayerHuman(client_index))
    return;
	
    if (GetConVarInt(gCvars[CVAR_ZMARKET_SPAWN]) == 1)
    {
       Market(client_index);
    }
	
    if (GetConVarInt(gCvars[CVAR_SPAWN_HE]) == 1)
	{
       GivePlayerItem(client_index, "weapon_hegrenade");
    }
	
    if (GetConVarInt(gCvars[CVAR_SPAWN_SMOKE]) == 1)
	{
       GivePlayerItem(client_index, "weapon_smokegrenade");
    }
	
}


public bool:OnClientConnect(client, String:rejectmsg[], maxlen)
{
// Zombie Names
	if (!GetConVarBool(gCvars[CVAR_ZOMBIENAMES]))
	{
		return true;
	}

	new loaded_names = GetArraySize(bot_names);

	if (IsFakeClient(client) && loaded_names != 0)
	{
		// we got a bot, here, boss
		
		decl String:newname[MAX_NAME_LENGTH];
		GetArrayString(bot_names, GetArrayCell(name_redirects, next_index), newname, MAX_NAME_LENGTH);

		next_index++;
		if (next_index > loaded_names - 1)
		{
			next_index = 0;
		}
		
		SetClientInfo(client, "name", newname);
	}
	return true;
// End Zombie Names
}

MapChangeCleanup()
{
    gDay = 0;
    
    ClearArray(restrictedWeapons);
    ClearTrie(trieDeaths);
    
    tAmbience = INVALID_HANDLE;
    tHUD = INVALID_HANDLE;
    tFreeze = INVALID_HANDLE;
}

CheckMapConfig()
{
    decl String:mapname[64];
    GetCurrentMap(mapname, sizeof(mapname));
    
    Format(gMapConfig, sizeof(gMapConfig), "%s/%s", gMapConfig, mapname);
    
    LoadZombieData(false);
}

ZRiotEnd()
{
    // Old CS_TerminateRound(3.0, CSRoundEnd_GameStart);
    // Alternative if needed: ServerCommand("mp_restartgame 3");
    
    SetHostname(hostname);
    
    UnhookCvars();
    UnhookEvents();
    
    ServerCommand("bot_all_weapons");
    ServerCommand("bot_kick");
    
    new maxplayers = GetMaxClients();
    for (new x = 1; x <= maxplayers; x++)
    {
        if (!IsClientInGame(x))
        {
            continue;
        }
        
        if (tRespawn[x] != INVALID_HANDLE)
        {
            CloseHandle(tRespawn[x]);
            tRespawn[x] = INVALID_HANDLE;
        }
    }
}
