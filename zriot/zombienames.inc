new Handle:bot_names;
new Handle:name_redirects;
new next_index;

GenerateRedirects()
{
	new loaded_names = GetArraySize(bot_names);

	if (name_redirects != INVALID_HANDLE)
	{
		ResizeArray(name_redirects, loaded_names);
	} else {
		name_redirects = CreateArray(1, loaded_names);
	}

	for (new i = 0; i < loaded_names; i++)
	{
		SetArrayCell(name_redirects, i, i);
		
		if (i == 0)
		{
			continue;
		}

		if (GetConVarBool(gCvars[CVAR_ZOMBIERANDOMNAME] ))
		{
			SwapArrayItems(name_redirects, GetRandomInt(0, i - 1), i);
		}
	}
}

ReloadNames()
{
	next_index = 0;
	decl String:path[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, path, sizeof(path), "configs/zriot/Zombie_Names.txt");
	
	if (bot_names != INVALID_HANDLE)
	{
		ClearArray(bot_names);
	} else {
		bot_names = CreateArray(MAX_NAME_LENGTH);
	}
	
	new Handle:file = OpenFile(path, "r");
	if (file == INVALID_HANDLE)
	{
		return;
	}
	
	// this LENGTH*3 is sort of a hack
	// don't make long lines, people!
	decl String:newname[MAX_NAME_LENGTH*3];
	decl String:formedname[MAX_NAME_LENGTH];
	decl String:prefix[MAX_NAME_LENGTH];

	GetConVarString(gCvars[CVAR_ZOMBIEPREFIX], prefix, MAX_NAME_LENGTH);

	while (IsEndOfFile(file) == false)
	{
		if (ReadFileLine(file, newname, sizeof(newname)) == false)
		{
			break;
		}
		
		// trim off comments starting with // or #
		new commentstart;
		commentstart = StrContains(newname, "//");
		if (commentstart != -1)
		{
			newname[commentstart] = 0;
		}
		commentstart = StrContains(newname, "#");
		if (commentstart != -1)
		{
			newname[commentstart] = 0;
		}
		
		new length = strlen(newname);
		if (length < 2)
		{
			// Blank
			continue;
		}

		TrimString(newname);
		
		Format(formedname, MAX_NAME_LENGTH, "%s %s", prefix, newname);
		PushArrayString(bot_names, formedname);
	}
	
	CloseHandle(file);
}

Zombienames_Default()
{
  RegServerCmd("zriot_zombienames_reload", Command_Reload);
}

public Action:Command_Reload(args)
{
	ReloadNames();
	GenerateRedirects();
	PrintToServer("[ZR] Loaded %i names.", GetArraySize(bot_names));
}

public Action:Event_PlayerTeamNames(Handle:event, const String:name[], bool:dontBroadcast)
{
	if (!(GetConVarBool(gCvars[CVAR_ZOMBIENAMES])))
	{
		return Plugin_Continue;
	}

	new client = GetClientOfUserId(GetEventInt(event, "userid"));
	if (client == 0)
	{
		// weird error, ignore
		return Plugin_Continue;
	}
	if (IsFakeClient(client))
	{
		// fake client == bot
		SetEventBool(event, "silent", true);
		return Plugin_Changed;
	}

	return Plugin_Continue;
}

public Action:Event_PlayerConnectNames(Handle:event, const String:name[], bool:dontBroadcast)
{
	if (!(GetConVarBool(gCvars[CVAR_ZOMBIENAMES])))
	{
		return Plugin_Continue;
	}

	decl String:networkID[32];
	GetEventString(event, "networkid", networkID, sizeof(networkID));

	if(!dontBroadcast && StrEqual(networkID, "BOT"))
	{
		// we got a bot connectin', resend event as no-broadcast
		decl String:clientName[MAX_NAME_LENGTH], String:address[32];
		GetEventString(event, "name", clientName, sizeof(clientName));
		GetEventString(event, "address", address, sizeof(address));

		new Handle:newEvent = CreateEvent("player_connect", true);
		SetEventString(newEvent, "name", clientName);
		SetEventInt(newEvent, "index", GetEventInt(event, "index"));
		SetEventInt(newEvent, "userid", GetEventInt(event, "userid"));
		SetEventString(newEvent, "networkid", networkID);
		SetEventString(newEvent, "address", address);

		FireEvent(newEvent, true);

		return Plugin_Handled;
	}

	return Plugin_Continue;
}

public Action:SayText2(UserMsg:msg_id, Handle:bf, players[], playersNum, bool:reliable, bool:init)
{
    if(!reliable)
    {
        return Plugin_Continue;
    }

    new String:buffer[25];

    if(GetUserMessageType() == UM_Protobuf) // CSGO
    {
        PbReadString(bf, "msg_name", buffer, sizeof(buffer));

        if(StrEqual(buffer, "#Cstrike_Name_Change"))
        {
            return Plugin_Handled;
        }
    }
    else // CSS
    {
        BfReadChar(bf);
        BfReadChar(bf);
        BfReadString(bf, buffer, sizeof(buffer));

        if(StrEqual(buffer, "#Cstrike_Name_Change"))
        {
            return Plugin_Handled;
        } 
    }
    return Plugin_Continue;
}  