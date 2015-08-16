Servercommands_configs()
{
    // Default Warmup Remove
    ServerCommand("mp_warmuptime 0");
    ServerCommand("mp_do_warmup_period 0");
	
	// Team Commands
    decl String:zombieteam[8];
    GetConVarString(gCvars[CVAR_ZOMBIETEAM], zombieteam, sizeof(zombieteam));
	
	// Teamnames
    if (StrEqual(zombieteam, "t", false))
    {
    ServerCommand("mp_teamname_1 Humans");
    ServerCommand("mp_teamname_2 Zombies");
    }
    else if (StrEqual(zombieteam, "ct", false))
    {
    ServerCommand("mp_teamname_1 Zombies");
    ServerCommand("mp_teamname_2 Humans");
    }
}