new Handle:restrictedWeapons = INVALID_HANDLE;

enum WepRestrictQuery
{
    Successful,  /** Weapon (un)restrict query was successful */
    Invalid,  /** Weapon invalid */
    Existing,  /** Already restricted */
}
    
InitWeaponRestrict()
{
    RegConsoleCmd("buy", BuyHook);
    
    restrictedWeapons = CreateArray(32, 0);
}

ClientHookUse(client)
{
	SDKHook(client, SDKHook_WeaponCanUse, Weapon_CanUse);
}

public Action:BuyHook(client, argc)
{
    new bool:enabled = GetConVarBool(gCvars[CVAR_ENABLE]);
    if (!enabled)
    {
        return Plugin_Continue;
    }
    
    if (IsPlayerZombie(client))
    {
        ZRiot_PrintToChat(client, "Zombie cant use weapon");
        
        return Plugin_Handled;
    }
    
    decl String:weapon[64];
    GetCmdArg(1, weapon, sizeof(weapon));
    
    ReplaceString(weapon, sizeof(weapon), "weapon_", "");
    
    if (IsWeaponRestricted(weapon))
    {
        ZRiot_PrintToChat(client, "Weapon is restricted", weapon);
        return Plugin_Handled;
    }
    
    return Plugin_Continue;
}

WepRestrictQuery:RestrictWeapon(const String:weapon[])
{
    if (IsWeaponGroup(weapon))
    {
        RestrictWeaponGroup(weapon);
        
        ZRiot_PrintToChat(0, "Weapon group has been restricted", weapon);
        
        return Successful;
    }
    
    if (!IsWeaponRestricted(weapon))
    {
        PushArrayString(restrictedWeapons, weapon);
        
        ZRiot_PrintToChat(0, "Weapon has been restricted", weapon);
        
        return Successful;
    }
    
    return Existing;
}

RestrictWeaponGroup(const String:group[])
{
    if (StrEqual(group, "pistols", false))
    {
        PushArrayString(restrictedWeapons, "glock");
        PushArrayString(restrictedWeapons, "p250");
        PushArrayString(restrictedWeapons, "hkp2000");
        PushArrayString(restrictedWeapons, "deagle");
        PushArrayString(restrictedWeapons, "elite");
        PushArrayString(restrictedWeapons, "tec9");
        PushArrayString(restrictedWeapons, "usp_silencer");
        PushArrayString(restrictedWeapons, "cz75a");
        PushArrayString(restrictedWeapons, "fiveseven");
    }
    else if (StrEqual(group, "heavy", false))
    {
        PushArrayString(restrictedWeapons, "xm1014");
        PushArrayString(restrictedWeapons, "mag7");
        PushArrayString(restrictedWeapons, "sawedoff");
        PushArrayString(restrictedWeapons, "nova");
        PushArrayString(restrictedWeapons, "m249");
        PushArrayString(restrictedWeapons, "negev");
    }
    else if (StrEqual(group, "smgs", false))
    {
        PushArrayString(restrictedWeapons, "mp9");
        PushArrayString(restrictedWeapons, "mac10");
        PushArrayString(restrictedWeapons, "mp7");
        PushArrayString(restrictedWeapons, "ump45");
        PushArrayString(restrictedWeapons, "p90");
        PushArrayString(restrictedWeapons, "bizon");
    }
    else if (StrEqual(group, "rifles", false))
    {
        PushArrayString(restrictedWeapons, "galilar");
        PushArrayString(restrictedWeapons, "famas");
        PushArrayString(restrictedWeapons, "ak47");
        PushArrayString(restrictedWeapons, "m4a1");
        PushArrayString(restrictedWeapons, "ssg08");
        PushArrayString(restrictedWeapons, "aug");
        PushArrayString(restrictedWeapons, "sg556");
        PushArrayString(restrictedWeapons, "awp");
        PushArrayString(restrictedWeapons, "scar20");
        PushArrayString(restrictedWeapons, "g3sg1");
        PushArrayString(restrictedWeapons, "m4a1_silencer");
    }
    else if (StrEqual(group, "gear", false))
    {
        PushArrayString(restrictedWeapons, "taser");
        PushArrayString(restrictedWeapons, "c4");
    }
    else if (StrEqual(group, "grenades", false))
    {
        PushArrayString(restrictedWeapons, "hegrenade");
        PushArrayString(restrictedWeapons, "flashbang");
        PushArrayString(restrictedWeapons, "smokegrenade");
        PushArrayString(restrictedWeapons, "molotov");
        PushArrayString(restrictedWeapons, "decoy");
    }
}
    
WepRestrictQuery:UnRestrictWeapon(const String:weapon[])
{
    if (IsWeaponGroup(weapon))
    {
        UnRestrictWeaponGroup(weapon);
        
        ZRiot_PrintToChat(0, "Weapon group has been unrestricted", weapon);
        
        return Successful;
    }
    
    new index = GetRestrictedWeaponIndex(weapon);
    
    if (index > -1)
    {
        RemoveFromArray(restrictedWeapons, index);
        
        ZRiot_PrintToChat(0, "Weapon has been unrestricted", weapon);
        
        return Successful;
    }

    return Invalid;
}

UnRestrictWeaponGroup(const String:group[])
{
    if (StrEqual(group, "pistols", false))
    {
        UnRestrictWeapon("glock");
        UnRestrictWeapon("p250");
        UnRestrictWeapon("hkp2000");
        UnRestrictWeapon("deagle");
        UnRestrictWeapon("elite");
        UnRestrictWeapon("tec9");
        UnRestrictWeapon("usp-s");
        UnRestrictWeapon("cZ75a");
        UnRestrictWeapon("fiveseven");
    }
    else if (StrEqual(group, "heavy", false))
    {
        UnRestrictWeapon("xm1014");
        UnRestrictWeapon("mag7");
        UnRestrictWeapon("sawedoff");
        UnRestrictWeapon("nova");
        UnRestrictWeapon("m249");
        UnRestrictWeapon("negev");
    }
    else if (StrEqual(group, "smgs", false))
    {
        UnRestrictWeapon("mp9");
        UnRestrictWeapon("mac10");
        UnRestrictWeapon("mp7");
        UnRestrictWeapon("ump45");
        UnRestrictWeapon("p90");
        UnRestrictWeapon("bizon");
    }
    else if (StrEqual(group, "rifles", false))
    {
        UnRestrictWeapon("galilar");
        UnRestrictWeapon("famas");
        UnRestrictWeapon("ak47");
        UnRestrictWeapon("m4a1");
        UnRestrictWeapon("ssg08");
        UnRestrictWeapon("aug");
        UnRestrictWeapon("sg556");
        UnRestrictWeapon("awp");
        UnRestrictWeapon("scar20");
        UnRestrictWeapon("g3sg1");
    }
    else if (StrEqual(group, "gear", false))
    {
        UnRestrictWeapon("taser");
        UnRestrictWeapon("c4");
    }
    else if (StrEqual(group, "grenades", false))
    {
        UnRestrictWeapon("hegrenade");
        UnRestrictWeapon("flashbang");
        UnRestrictWeapon("smokegrenade");
        UnRestrictWeapon("molotov");
        UnRestrictWeapon("decoy");
    }
}

bool:IsWeaponRestricted(const String:weapon[])
{
    for (new x = 0; x < GetArraySize(restrictedWeapons); x++)
    {
        decl String:restrictedweapon[32];
        GetArrayString(restrictedWeapons, x, restrictedweapon, sizeof(restrictedweapon));
        
        if (StrEqual(weapon, restrictedweapon, false))
        {
            return true;
        }
    }
    
    return false;
}

GetRestrictedWeaponIndex(const String:weapon[])
{
    for (new x = 0; x < GetArraySize(restrictedWeapons); x++)
    {
        decl String:restrictedweapon[32];
        GetArrayString(restrictedWeapons, x, restrictedweapon, sizeof(restrictedweapon));
        ReplaceString(restrictedweapon, sizeof(restrictedweapon), "weapon_", "");
        
        if (StrEqual(weapon, restrictedweapon, false))
        {
            return x;
        }
    }
    
    return -1;
}

bool:IsWeaponGroup(const String:weapon[])
{
  return (StrEqual(weapon, "pistols", false) || StrEqual(weapon, "heavy", false) || StrEqual(weapon, "smgs", false) || StrEqual(weapon, "rifles", false) || StrEqual(weapon, "gear", false) || StrEqual(weapon, "grenades", false));
}

public Action:Weapon_CanUse(client, weapon)
{
    new bool:enabled = GetConVarBool(gCvars[CVAR_ENABLE]);
    if (!enabled)
    {
        return Plugin_Continue;
    }
        
    new String:weaponname[32];
    if (!weapon || !GetEdictClassname(weapon, weaponname, sizeof(weaponname)))
    {
        return Plugin_Continue;
    }
    
    ReplaceString(weaponname, sizeof(weaponname), "weapon_", "");
    
    decl String:model[256];
    GetClientModel(client, model, sizeof(model));
    
    ReplaceString(model, sizeof(model), ".mdl", "");
    
    if (FindStringInArray(adtModels, model) > -1 && !StrEqual(weaponname, "knife"))
    {
        return Plugin_Handled;
    }
    
    if (IsWeaponRestricted(weaponname))
    {
        return Plugin_Handled;
    }
    
    if (IsPlayerZombie(client) && !StrEqual(weaponname, "knife"))
    {
        if (StrEqual(weaponname, "glock") || StrEqual(weaponname, "usp"))
        {
            CreateTimer(0.0, RemoveSpawnWeapon, weapon);
        }
        
        return Plugin_Handled;
    }
    
    return Plugin_Continue;
}

public Action:RemoveSpawnWeapon(Handle:timer, any:weapon)
{
    if (IsValidEdict(weapon))
    {
        RemoveEdict(weapon);
	}
}