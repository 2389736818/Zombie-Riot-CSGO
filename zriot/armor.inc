public Action:Armor_Helmet(Handle:event, const String:name[], bool:dontBroadcast)
{
	new client = GetClientOfUserId(GetEventInt(event, "userid"));
	if (IsPlayerAlive(client))
	{
		new team = GetClientTeam(client);
		if (team == 3 && GetConVarInt(gCvars[CVAR_ARMOR_HELMET]) == 1)
		{
			GivePlayerItem( client, "item_assaultsuit"); 
			SetEntProp(client, Prop_Send, "m_ArmorValue", 100, 1);
		}
	}
}