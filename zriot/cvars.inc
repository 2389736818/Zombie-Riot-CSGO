enum ZRiotSettings
{
    Handle:CVAR_ENABLE,
    Handle:CVAR_AMBIENCE,
    Handle:CVAR_AMBIENCE_FILE,
    Handle:CVAR_AMBIENCE_LENGTH,
    Handle:CVAR_AMBIENCE_VOLUME,
    Handle:CVAR_HOSTNAME_UPDATE,
    Handle:CVAR_NOBLOCK,
    Handle:CVAR_FREEZE,
    Handle:CVAR_BOTQUOTA_SILENT,
    Handle:CVAR_REGRESSION,
    Handle:CVAR_FIRST_RESPAWN,
    Handle:CVAR_RESPAWN,
    Handle:CVAR_ZOMBIETEAM,
    Handle:CVAR_ZOMBIEMAX,
    Handle:CVAR_HUD,
    Handle:CVAR_TARGETING,
    Handle:CVAR_ROUNDFADE,
    Handle:CVAR_RAGDOLL_REMOVE,
    Handle:CVAR_NAPALM,
    Handle:CVAR_NAPALM_TIME,
    Handle:CVAR_DARK,
    Handle:CVAR_DARK_LEVEL,
    Handle:CVAR_DARK_SKY,
    Handle:CVAR_ZMARKET_BUYZONE,
    Handle:CVAR_CASHFILL,
	Handle:CVAR_CASHAMOUNT,
    Handle:CVAR_OVERLAYS,
    Handle:CVAR_OVERLAYS_ZOMBIE,
    Handle:CVAR_OVERLAYS_HUMAN,
    // Custom CVAR
    Handle:CVAR_DIFFICULT_2,
    Handle:CVAR_DIFFICULT_3,
    Handle:CVAR_COOLDOWN,
	Handle:CVAR_ZOMBIENAMES,
    Handle:CVAR_ZOMBIEPREFIX,
	Handle:CVAR_ZOMBIERANDOMNAME,
    Handle:CVAR_ZMARKET_SPAWN,
    Handle:CVAR_SPAWN_SMOKE,
    Handle:CVAR_SPAWN_HE,
    Handle:CVAR_ARMOR_HELMET,
    Handle:CVAR_NOBUYZONE
}

new gCvars[ZRiotSettings];

CreateCvars()
{
    gCvars[CVAR_ENABLE]                =    CreateConVar("zriot_enable", "1", "Enable ZombieRiot gameplay (0: Disable)");
    gCvars[CVAR_AMBIENCE]              =    CreateConVar("zriot_ambience", "1", "Enable creepy ambience to be played throughout the game (0: Disable)");
    gCvars[CVAR_AMBIENCE_FILE]         =    CreateConVar("zriot_ambience_file", "ambient/zr/zr_ambience.mp3", "Path to ambient sound file that will be played throughout the game, when zriot_ambience is 1");
    gCvars[CVAR_AMBIENCE_LENGTH]       =    CreateConVar("zriot_ambience_length", "60.0", "The length, in seconds, of the ambient sound file");
    gCvars[CVAR_AMBIENCE_VOLUME]       =    CreateConVar("zriot_ambience_volume", "0.6", "Volume of ambient sounds when zriot_ambience is 1 (0.0: Unhearable,  1.0: Max volume)");
    gCvars[CVAR_HOSTNAME_UPDATE]       =    CreateConVar("zriot_hostname_update", "1", "Updates the server's hostname to display the current day server is playing (0: Disable)");
    gCvars[CVAR_REGRESSION]            =    CreateConVar("zriot_regression", "1", "If the zombies win the round, the game will regress one day (0: Disable)");
    gCvars[CVAR_NOBLOCK]               =    CreateConVar("zriot_noblock", "1", "Prevents zombies from getting stuck in each other (0: Disable)");
    gCvars[CVAR_FREEZE]                =    CreateConVar("zriot_freeze", "10", "Time, in seconds, to freeze zombies at round start to allow humans to get set up (0: Disable)");
    gCvars[CVAR_BOTQUOTA_SILENT]       =    CreateConVar("zriot_botquota_silent", "1", "Blocks join/leave text for bots (0: Disable)");
    gCvars[CVAR_FIRST_RESPAWN]         =    CreateConVar("zriot_first_respawn", "10", "Amount of time to wait before spawning a player into the game for the first time (0: Disable)");
    gCvars[CVAR_RESPAWN]               =    CreateConVar("zriot_respawn", "30", "Amount of time each human has to wait before they will respawn into the game (0: Disable)");
    gCvars[CVAR_ZOMBIETEAM]            =    CreateConVar("zriot_zombieteam", "t", "Which team zombie's will be on (t: Terrorist ct: Counter-Terrorist)");
    gCvars[CVAR_ZOMBIEMAX]             =    CreateConVar("zriot_zombiemax", "12", "The max amount of zombies spawned at one time");
    gCvars[CVAR_HUD]                   =    CreateConVar("zriot_hud", "1", "Enable persistent display of the HUD which displays day, zombies left, and humans left (0: Disable)");
    gCvars[CVAR_TARGETING]             =    CreateConVar("zriot_targeting", "1", "Enables a system that tracks damage done to each zombie, and shows you each one's current health (0: Disable)");
    gCvars[CVAR_ROUNDFADE]             =    CreateConVar("zriot_roundfade", "0", "Player's screens fade blue if humans win, red if zombies in, and black in any other case (0: Disable)");
    gCvars[CVAR_RAGDOLL_REMOVE]        =    CreateConVar("zriot_ragdoll_remove", "20", "The time, in seconds, before the ragdoll of dead zombies will be deleted (0: Disable)");
    gCvars[CVAR_NAPALM]                =    CreateConVar("zriot_napalm", "1", "Turns grenades into napalm grenades that light zombies on fire (0: Disable)");
    gCvars[CVAR_NAPALM_TIME]           =    CreateConVar("zriot_napalm_time", "20", "How long the zombie burns when zr_napalm is 1");
    gCvars[CVAR_DARK]                  =    CreateConVar("zriot_dark", "0", "Darkens the map (0: Disable)");
    gCvars[CVAR_DARK_LEVEL]            =    CreateConVar("zriot_dark_level", "a", "The darkness of the map,  a being the darkest,  z being extremely bright when zriot_dark is 1 (n: Default)");
    gCvars[CVAR_DARK_SKY]              =    CreateConVar("zriot_dark_sky", "cs_baggage_skybox_", "The sky the map will have when zriot_dark is 1");
    gCvars[CVAR_ZMARKET_BUYZONE]       =    CreateConVar("zriot_market_buyzone", "0", "Must be in buyzone to access !zmarket, if Market is installed (0: Can be used anywhere)");
    gCvars[CVAR_CASHFILL]              =    CreateConVar("zriot_cashfill", "1", "Enable the mod to set the players cash to zriot_cashamount (0: Disabled)");
    gCvars[CVAR_CASHAMOUNT]            =    CreateConVar("zriot_cashamount", "12000", "How much money players will have when they spawn when zriot_cashfill is 1");
    gCvars[CVAR_OVERLAYS]              =    CreateConVar("zriot_overlays", "1", "Enable use of round end overlays to show the winner (0: Disable)");
    gCvars[CVAR_OVERLAYS_ZOMBIE]       =    CreateConVar("zriot_overlays_zombie", "overlays/sfzr/zombies", "Path to overlay shown when Zombies win, when zriot_overlays is 1");
    gCvars[CVAR_OVERLAYS_HUMAN]        =    CreateConVar("zriot_overlays_human", "overlays/sfzr/humans", "Path to overlay shown when Humans win, when zriot_overlays is 1");

    // New CVARS
    gCvars[CVAR_DIFFICULT_2]           =    CreateConVar("zriot_difficult_2", "3", "How much players to start Difficult 2? (3: Default)");
    gCvars[CVAR_DIFFICULT_3]           =    CreateConVar("zriot_difficult_3", "6", "How much players to start Difficult 3? (6: Default)");
    gCvars[CVAR_COOLDOWN]              =    CreateConVar("zriot_weaponcooldown", "0", "Enable Weapon Cooldown for different weapons. (0: Default)");
    gCvars[CVAR_ZOMBIENAMES]           =    CreateConVar("zriot_zombienames", "1", "Enable Zombie Prefix & Custom names. (1: Default)");
    gCvars[CVAR_ZOMBIEPREFIX]          =    CreateConVar("zriot_zombieprefix", "Zombie", "Set Zombie Prefix (Zombie: Default)");
    gCvars[CVAR_ZOMBIERANDOMNAME]      =    CreateConVar("zriot_zombierandomname", "1", "Randomize Zombie Names (1: Default)");
    gCvars[CVAR_ZMARKET_SPAWN]         =    CreateConVar("zriot_market_spawn", "0", "Show !market on spawn (0: Default)");
    gCvars[CVAR_SPAWN_SMOKE]           =    CreateConVar("zriot_spawn_smokegrenade", "0", "Give Humans a smoke grenade on spawn (0: Default)");
    gCvars[CVAR_SPAWN_HE]              =    CreateConVar("zriot_spawn_hegrenade", "0", "Give Humans a he grenade on spawn (0: Default)");
    gCvars[CVAR_NOBUYZONE]             =    CreateConVar("zriot_remove_buyzone", "0", "Remove Map Buyzone(s) (0: Default)");
    gCvars[CVAR_ARMOR_HELMET]          =    CreateConVar("zriot_human_armor", "0", "Give Helmet + Armor on spawn (0: Default)");
	
    // Others
    HookConVarChange(gCvars[CVAR_ENABLE], EnableHook);
    // Generate Config
    AutoExecConfig(true, "zriot", "sourcemod/zriot");
}

HookCvars()
{
    SetConVarBool(FindConVar("mp_autoteambalance"), false);
    SetConVarInt(FindConVar("mp_limitteams"), 0);
// Default Convar Hooks
    HookConVarChange(FindConVar("mp_autoteambalance"), AutoTeamBalanceHook);
    HookConVarChange(FindConVar("mp_limitteams"), LimitTeamsHook);
    HookConVarChange(gCvars[CVAR_ZOMBIETEAM], ZombieTeamHook);
    HookConVarChange(FindConVar("mp_restartgame"), RestartGameHook);
// Ammo Cooldown Configuration
    HookConVarChange(gCvars[CVAR_COOLDOWN] , OnPluginToggle);
    HookEventEx("weapon_fire", OnWeaponFire);
// Zombie Names
    HookEvent("player_connect", Event_PlayerConnectNames, EventHookMode_Pre);
    HookEvent("player_team", Event_PlayerTeamNames, EventHookMode_Pre);
    HookUserMessage(GetUserMessageId("SayText2"), SayText2, true);
// Player Spawn (Market)
    HookEvent("player_spawn", Event_PlayerSpawn);
// Player Spawn (Armor)
    HookEvent("player_spawn", Armor_Helmet);
}

UnhookCvars()
{
    UnhookConVarChange(FindConVar("mp_autoteambalance"), AutoTeamBalanceHook);
    UnhookConVarChange(FindConVar("mp_limitteams"), LimitTeamsHook);
    UnhookConVarChange(gCvars[CVAR_ZOMBIETEAM], ZombieTeamHook);
    UnhookConVarChange(FindConVar("mp_restartgame"), RestartGameHook);
}

public EnableHook(Handle:convar, const String:oldValue[], const String:newValue[])
{
    new bool:enable = bool:StringToInt(newValue);
    
    if (enable)
    {
        FindMapSky();
        
        FindHostname();
        UpdateHostname();
        
        HookEvents();
        HookCvars();
        
        ServerCommand("bot_kick");
        
        gDay = 0;
        
        CS_TerminateRound(3.0, CSRoundEnd_GameStart);
    }
    else
    {
        ZRiotEnd();
    }
}

public AutoTeamBalanceHook(Handle:convar, const String:oldValue[], const String:newValue[])
{
    SetConVarBool(convar, false);
}

public LimitTeamsHook(Handle:convar, const String:oldValue[], const String:newValue[])
{
    SetConVarInt(convar, 0);
}

public ZombieTeamHook(Handle:convar, const String:oldValue[], const String:newValue[])
{
    if (StrEqual(newValue, "t", false) || StrEqual(newValue, "ct", false))
    {
        UpdateTeams();
    }
}

public RestartGameHook(Handle:convar, const String:oldValue[], const String:newValue[])
{
    gDay = 0;
    
    ResetZombies(true);
}
