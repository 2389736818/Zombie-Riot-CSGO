enum ZRiot_DayData
{
    String:data_display[32],
    String:data_zombieoverride[32*MAXZOMBIES],
    String:data_storyline[192],
    data_count,
	data_maxspawn,
    data_healthboost,
    bool:data_respawn,
    data_deaths_before_zombie,
    Float:data_fademin,
    Float:data_fademax
}

#define MAXDAYS 26

new Handle:kvDays = INVALID_HANDLE;
new arrayDays[MAXDAYS][ZRiot_DayData];
new arrayDays_Difficult_1[MAXDAYS][ZRiot_DayData];
new arrayDays_Difficult_2[MAXDAYS][ZRiot_DayData];
new arrayDays_Difficult_3[MAXDAYS][ZRiot_DayData];
new dCount;

stock GetRealClientCount( bool:inGameOnly = true ) {
 	new clients = 0;
 	for( new i = 1; i <= GetMaxClients(); i++ ) {
 		if( ( ( inGameOnly ) ? IsClientInGame( i ) : IsClientConnected( i ) ) && !IsFakeClient( i ) ) {
 			clients++;
 		}
 	}
 	return clients;
 }

LoadDayDataDif1(bool:defaultconfig)
{
    decl String:path[PLATFORM_MAX_PATH];
    Format(path, sizeof(path), "%s/Days_Difficult_1.txt", gMapConfig); 
    	
    if (!defaultconfig && !FileExists(path))
    {
        return;
    }

    
	
    if (kvDays != INVALID_HANDLE)
    {
        CloseHandle(kvDays);
    }
    
    kvDays = CreateKeyValues("days");
    KvSetEscapeSequences(kvDays, true);
    
    if (!FileToKeyValues(kvDays, path))
    {
        SetFailState("\"%s\" failed to load", path);
    }
    
    KvRewind(kvDays);
    if (!KvGotoFirstSubKey(kvDays))
    {
        SetFailState("No day data defined in \"%s\"", path);
    }
    
    decl String:display[32];
    decl String:zombieoverride[32*MAXZOMBIES];
    decl String:storyline[192];
    
    dCount = 0;
    do
    {
        KvGetSectionName(kvDays, display, sizeof(display));
        strcopy(arrayDays_Difficult_1[dCount][data_display], 32, display);
        
        KvGetString(kvDays, "zombieoverride", zombieoverride, sizeof(zombieoverride));
        strcopy(arrayDays_Difficult_1[dCount][data_zombieoverride], 32*MAXZOMBIES, zombieoverride);
        
        KvGetString(kvDays, "storyline", storyline, sizeof(storyline));
        strcopy(arrayDays_Difficult_1[dCount][data_storyline], 192, storyline);
        
        arrayDays_Difficult_1[dCount][data_count] = KvGetNum(kvDays, "count", 25);
        arrayDays_Difficult_1[dCount][data_maxspawn] = KvGetNum(kvDays, "maxspawn");
        arrayDays_Difficult_1[dCount][data_healthboost] = KvGetNum(kvDays, "healthboost");
        arrayDays_Difficult_1[dCount][data_respawn] = bool:KvGetNum(kvDays, "respawn");
        arrayDays_Difficult_1[dCount][data_deaths_before_zombie] = KvGetNum(kvDays, "deaths_before_zombie");
        arrayDays_Difficult_1[dCount][data_fademin] = KvGetFloat(kvDays, "fademin");
        arrayDays_Difficult_1[dCount][data_fademax] = KvGetFloat(kvDays, "fademax");
        
        dCount++;
    } while (KvGotoNextKey(kvDays));
}

LoadDayDataDif2(bool:defaultconfig)
{
    decl String:path[PLATFORM_MAX_PATH];
    Format(path, sizeof(path), "%s/Days_Difficult_2.txt", gMapConfig); 
    	
    if (!defaultconfig && !FileExists(path))
    {
        return;
    }

    
	
    if (kvDays != INVALID_HANDLE)
    {
        CloseHandle(kvDays);
    }
    
    kvDays = CreateKeyValues("days");
    KvSetEscapeSequences(kvDays, true);
    
    if (!FileToKeyValues(kvDays, path))
    {
        SetFailState("\"%s\" failed to load", path);
    }
    
    KvRewind(kvDays);
    if (!KvGotoFirstSubKey(kvDays))
    {
        SetFailState("No day data defined in \"%s\"", path);
    }
    
    decl String:display[32];
    decl String:zombieoverride[32*MAXZOMBIES];
    decl String:storyline[192];
    
    dCount = 0;
    do
    {
        KvGetSectionName(kvDays, display, sizeof(display));
        strcopy(arrayDays_Difficult_2[dCount][data_display], 32, display);
        
        KvGetString(kvDays, "zombieoverride", zombieoverride, sizeof(zombieoverride));
        strcopy(arrayDays_Difficult_2[dCount][data_zombieoverride], 32*MAXZOMBIES, zombieoverride);
        
        KvGetString(kvDays, "storyline", storyline, sizeof(storyline));
        strcopy(arrayDays_Difficult_2[dCount][data_storyline], 192, storyline);
        
        arrayDays_Difficult_2[dCount][data_count] = KvGetNum(kvDays, "count", 25);
        arrayDays_Difficult_2[dCount][data_maxspawn] = KvGetNum(kvDays, "maxspawn");
        arrayDays_Difficult_2[dCount][data_healthboost] = KvGetNum(kvDays, "healthboost");
        arrayDays_Difficult_2[dCount][data_respawn] = bool:KvGetNum(kvDays, "respawn");
        arrayDays_Difficult_2[dCount][data_deaths_before_zombie] = KvGetNum(kvDays, "deaths_before_zombie");
        arrayDays_Difficult_2[dCount][data_fademin] = KvGetFloat(kvDays, "fademin");
        arrayDays_Difficult_2[dCount][data_fademax] = KvGetFloat(kvDays, "fademax");
        
        dCount++;
    } while (KvGotoNextKey(kvDays));
}

LoadDayDataDif3(bool:defaultconfig)
{
    decl String:path[PLATFORM_MAX_PATH];
    Format(path, sizeof(path), "%s/Days_Difficult_3.txt", gMapConfig); 
    	
    if (!defaultconfig && !FileExists(path))
    {
        return;
    }

    
	
    if (kvDays != INVALID_HANDLE)
    {
        CloseHandle(kvDays);
    }
    
    kvDays = CreateKeyValues("days");
    KvSetEscapeSequences(kvDays, true);
    
    if (!FileToKeyValues(kvDays, path))
    {
        SetFailState("\"%s\" failed to load", path);
    }
    
    KvRewind(kvDays);
    if (!KvGotoFirstSubKey(kvDays))
    {
        SetFailState("No day data defined in \"%s\"", path);
    }
    
    decl String:display[32];
    decl String:zombieoverride[32*MAXZOMBIES];
    decl String:storyline[192];
    
    dCount = 0;
    do
    {
        KvGetSectionName(kvDays, display, sizeof(display));
        strcopy(arrayDays_Difficult_3[dCount][data_display], 32, display);
        
        KvGetString(kvDays, "zombieoverride", zombieoverride, sizeof(zombieoverride));
        strcopy(arrayDays_Difficult_3[dCount][data_zombieoverride], 32*MAXZOMBIES, zombieoverride);
        
        KvGetString(kvDays, "storyline", storyline, sizeof(storyline));
        strcopy(arrayDays_Difficult_3[dCount][data_storyline], 192, storyline);
        
        arrayDays_Difficult_3[dCount][data_count] = KvGetNum(kvDays, "count", 25);
        arrayDays_Difficult_3[dCount][data_maxspawn] = KvGetNum(kvDays, "maxspawn");
        arrayDays_Difficult_3[dCount][data_healthboost] = KvGetNum(kvDays, "healthboost");
        arrayDays_Difficult_3[dCount][data_respawn] = bool:KvGetNum(kvDays, "respawn");
        arrayDays_Difficult_3[dCount][data_deaths_before_zombie] = KvGetNum(kvDays, "deaths_before_zombie");
        arrayDays_Difficult_3[dCount][data_fademin] = KvGetFloat(kvDays, "fademin");
        arrayDays_Difficult_3[dCount][data_fademax] = KvGetFloat(kvDays, "fademax");
        
        dCount++;
    } while (KvGotoNextKey(kvDays));
}

GetDayDisplay(day, String:display[], len)
{
    new pCount;
    pCount = GetRealClientCount();
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    strcopy(display, len, arrayDays_Difficult_1[day][data_display]);
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    strcopy(display, len, arrayDays_Difficult_2[day][data_display]);
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    strcopy(display, len, arrayDays_Difficult_3[day][data_display]);
    }
}

GetMaxSpawn(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new maxSpawn;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    maxSpawn = arrayDays_Difficult_1[day][data_maxspawn];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    maxSpawn = arrayDays_Difficult_2[day][data_maxspawn];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    maxSpawn = arrayDays_Difficult_3[day][data_maxspawn];
    }
    return maxSpawn;
}

bool:ExplodeZombieOverrides(day)
{

    if (adtZombies != INVALID_HANDLE)
    {
        CloseHandle(adtZombies);
        adtZombies = INVALID_HANDLE;
    }
    
    decl String:zombieoverride[32*MAXZOMBIES];
    GetDayZombieOverride(day, zombieoverride, sizeof(zombieoverride));
    
    if (zombieoverride[0])
    {
        adtZombies = CreateArray();
        
        new String:sZombies[MAXZOMBIES][64];
        ExplodeString(zombieoverride, ",", sZombies, MAXZOMBIES, 64);
        
        for (new x = 0; x < MAXZOMBIES; x++)
        {
            if (!sZombies[x][0])
                continue;
            
            TrimString(sZombies[x]);
            new zombieid = FindZombieIDByName(sZombies[x]);
            
            if (zombieid == -1)
                continue;
            
            PushArrayCell(adtZombies, zombieid);
        }
        
        return true;
    }
    
    return false;
}

GetDayZombieOverride(day, String:zombieoverride[], len)
{
    new pCount;
    pCount = GetRealClientCount();
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    strcopy(zombieoverride, len, arrayDays_Difficult_1[day][data_zombieoverride]);
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    strcopy(zombieoverride, len, arrayDays_Difficult_2[day][data_zombieoverride]);
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    strcopy(zombieoverride, len, arrayDays_Difficult_3[day][data_zombieoverride]);
    }
}

GetDayStoryLine(day, String:storyline[], len)
{
    strcopy(storyline, len, arrayDays[day][data_storyline]);
}

GetDayCount(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new DayCount;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    DayCount = arrayDays_Difficult_1[day][data_count];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    DayCount = arrayDays_Difficult_2[day][data_count];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    DayCount = arrayDays_Difficult_3[day][data_count];
    }
    return DayCount;
}

GetDayHealthBoost(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new HealthBoost;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    HealthBoost = arrayDays_Difficult_1[day][data_healthboost];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    HealthBoost = arrayDays_Difficult_2[day][data_healthboost];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    HealthBoost = arrayDays_Difficult_3[day][data_healthboost];
    }
    return HealthBoost;
}

bool:GetDayRespawn(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new bool:RespawnValue;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    RespawnValue = arrayDays_Difficult_1[day][data_respawn];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    RespawnValue = arrayDays_Difficult_2[day][data_respawn];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    RespawnValue = arrayDays_Difficult_3[day][data_respawn];
    }
    return RespawnValue;
}

GetDayDeathsBeforeZombie(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new DeathsBeforeZombie;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    DeathsBeforeZombie = arrayDays_Difficult_1[day][data_deaths_before_zombie];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    DeathsBeforeZombie = arrayDays_Difficult_2[day][data_deaths_before_zombie];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    DeathsBeforeZombie = arrayDays_Difficult_3[day][data_deaths_before_zombie];
    }
    return DeathsBeforeZombie;
}

Float:GetDayMinFade(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new Float:MinFade;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    MinFade = arrayDays_Difficult_1[day][data_fademin];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    MinFade = arrayDays_Difficult_2[day][data_fademin];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    MinFade = arrayDays_Difficult_3[day][data_fademin];
    }
    return MinFade;
}

Float:GetDayMaxFade(day)
{
    new pCount;
    pCount = GetRealClientCount();
    new Float:MaxFade;
    if(pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_2]))
    {
    MaxFade = arrayDays_Difficult_1[day][data_fademax];
    }
    if((pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_2])) && (pCount <= GetConVarInt(gCvars[CVAR_DIFFICULT_3])))
    {
    MaxFade = arrayDays_Difficult_2[day][data_fademax];
    }
    if(pCount > GetConVarInt(gCvars[CVAR_DIFFICULT_3]))
    {
    MaxFade = arrayDays_Difficult_3[day][data_fademax];
	}
    return MaxFade;
}

BeginDay()
{
    gZombiesKilled = 0;

    new zombiecount = GetMaxSpawn(gDay);
    
    ServerCommand("bot_quota %d", zombiecount);
    
    decl String:display[32];

    GetDayDisplay(gDay, display, sizeof(display));
    
    new bool:override = ExplodeZombieOverrides(gDay);
    
    new maxplayers = GetMaxClients();
    for (new x = 1; x <= maxplayers; x++)
    {
        if (!IsClientInGame(x))
        {
            continue;
        }
        
        ChangeClientDeathCount(x, 0);
        
        if (!IsPlayerZombie(x))
        {
            continue;
        }
        
        if (override)
        {
            new size = GetArraySize(adtZombies);
            if (size)
            {
                new zombieid = GetRandomInt(0, size - 1);
                            
                Zombify(x, GetArrayCell(adtZombies, zombieid));
            }
        }
    }
}