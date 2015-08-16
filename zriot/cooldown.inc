new Handle:WeaponsTrie, m_flNextAttack;

enum
{
	maxshots,      // max. shots before cooldown
	Float:fldelay, // delay between shots
	array_size     // size of trie array
};

Cooldown_Map()
{
    if ((m_flNextAttack = FindSendPropOffs("CBasePlayer", "m_flNextAttack")) == -1)
    {
    SetFailState("Fatal Error: Unable to find prop offset \"CBasePlayer::m_flNextAttack\"!");
    }

	// Simulates late load for a plugin
    OnPluginToggle(gCvars[CVAR_COOLDOWN], "0", "1");

	// Create trie with cooldown settings
    WeaponsTrie = CreateTrie();
}

public OnPluginToggle(Handle:convar, const String:oldValue[], const String:newValue[])
{
	// Loop through all clients
	for (new client = 1; client <= MaxClients; client++)
	{
		// Ignore all not ingame players
		if (!IsClientInGame(client)) continue;

		// Get the new changed value
		switch (StringToInt(newValue))
		{
			// Hook or unhook callback appropriately
			case false: SDKUnhook(client, SDKHook_FireBulletsPost, OnFireBullets);
			case true:  SDKHookEx(client, SDKHook_FireBulletsPost, OnFireBullets);
		}
	}
}

Cooldown_Start()
{
	// Get the config and set weapons trie values eventually
    decl String:filepath[PLATFORM_MAX_PATH], Handle:file, cooldown[array_size];
    BuildPath(Path_SM, filepath, sizeof(filepath), "configs/zriot/Weapon_Cooldown.txt");

	// Check whether or not plugin config is exists
    if ((file = OpenFile(filepath, "r")) != INVALID_HANDLE)
	{
		ClearTrie(WeaponsTrie);

		decl String:fileline[PLATFORM_MAX_PATH];
		decl String:datas[3][PLATFORM_MAX_PATH];

		// Read every line in config and get rid of pieces
		while (ReadFileLine(file, fileline, sizeof(fileline)))
		{
			if (ExplodeString(fileline, ";", datas, sizeof(datas), sizeof(datas[])) == 3)
			{
				// Retrieve all required values to write in trie array
				cooldown[maxshots] = StringToInt(datas[1]);
				cooldown[fldelay]  = StringToFloat(datas[2]);
				SetTrieArray(WeaponsTrie, datas[0], cooldown, array_size);
			}
		}
	}
	else SetFailState("Unable to load plugin configuration file \"%s\"!", file);

	// Close config handle
    CloseHandle(file);
}

public OnWeaponFire(Handle:event, const String:name[], bool:dontBroadcast)
{
	// Check if plugin is enabled at the event
	if (GetConVarBool(gCvars[CVAR_COOLDOWN]))
	{
		// Retrieve the weapon string from event key
		decl String:weapon[PLATFORM_MAX_PATH];
		GetEventString(event, "weapon", weapon, sizeof(weapon));

		// Make FireBullets callback from event
		OnFireBullets(GetClientOfUserId(GetEventInt(event, "userid")), 0, weapon);
	}
}

public OnFireBullets(client, dummy, const String:weaponname[])
{
	decl cooldown[array_size];
	if (GetTrieArray(WeaponsTrie, weaponname, cooldown, array_size))
	{
		/**
		* For some reason second param (dummy) in FireBulletsPost callback is not static
		* So it means that shots aren't calculated when weapon fires, but it works fine for shotguns probably
		* I have to use static here to properly calculate shots when callback is fired due to plugin features.
		*/
		static shots;
		if (++shots >= cooldown[maxshots])
		{
			// Reset all shots
			shots = 0;

			// Prevnet player from firing for defined cooldown
			SetEntDataFloat(client, m_flNextAttack, GetGameTime() + cooldown[fldelay]);
		}
	}
}

Cooldown_On(client)
{
    if (GetConVarBool(gCvars[CVAR_COOLDOWN]))
	{
	// Hook every connected player if plugin enabled
    SDKHookEx(client, SDKHook_FireBulletsPost, OnFireBullets);
	}
}