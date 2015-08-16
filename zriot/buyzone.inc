new DelBuy;

RemoveBuyZone()
{
	decl String:Remove[65];
	DelBuy = GetMaxEntities();
	for (new i = 64; i <= DelBuy; i++)
	{
		if(IsValidEdict(i) && IsValidEntity(i) && (GetConVarInt(gCvars[CVAR_NOBUYZONE]) == 1))
		{
			GetEdictClassname(i, Remove, sizeof(Remove));
			if(StrEqual("func_buyzone", Remove))
			{
				RemoveEdict(i);
			}
		}
	}
}