/******************************************************************************
 *				MASTER SERVER INCLUDES - Groups 							  *
 *	@Descri��o:																  *
 *		Adiciona fun��es para de manipula��o de grupos, para jogadores.		  *
 *		Voc� pode separar admins, gangs, policiais entre outros em grupos	  *
 *		diferentes para utilizar fun��es espec�ficas para cada um.			  *
 *	@Legal:																	  *
 *		Este c�digo-fonte est� sob os termos de licen�a da Mozilla Public	  *
 *		License, v. 2.0. Se uma c�pia do MPL n�o for distribuida com este 	  *
 *		arquivo, voc� pode obter uma em http://mozilla.org/MPL/2.0/			  *
 *																			  *
 *		Os iniciais desenvolvedores deste c�digo � Larceny e L�s.			  *
 *		C�digos criados pelos iniciais desenvolvedores s�o Copyright (C) 2013 *
 *		Iniciais desenvolvedores.											  *
 *  											Todos os direitos reservados. *
 *	@Vers�o:																  *
 *		-																	  *
 *	@Autores:																  *
 *		Larceny,															  *
 *		L�s.																  *
 ******************************************************************************/

#include <a_samp>

#if defined _MSi_groups_included
	#endinput
#endif
#define _MSi_groups_included

/*
native CreateGroup(groupname[], type = INVALID_GROUP_TYPE);
native SendGroupTypeMessage(grouptype, color, message[]);
native RemovePlayerFromGroup(playerid, groupid);
native AddPlayerToGroup(playerid, groupid);
native SendGroupMessage(color, message[]);
native IsPlayerInGroup(playerid, groupid);
native SetGroupName(groupid, groupname[]);
native SetGroupType(groupid, grouptype);
native GetGroupIDbyName(groupname[]);
native GetGroupName(groupid);
native GetGroupType(groupid);
*/

#if !defined MAX_GROUPS
	#define MAX_GROUPS 32
#endif

#if !defined MAX_GROUP_NAME
	#define MAX_GROUP_NAME 32
#endif

#define INVALID_GROUP_TYPE 	-1
#define INVALID_GROUP_ID 	-1

enum E_GROUP_DATA
{
	E_GROUP_NAME[MAX_GROUP_NAME],
	E_GROUP_TYPE
}
static g_eGroupData[MAX_GROUPS][E_GROUP_DATA];

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Criar um grupo.

	Params:
		- groupname[]: Nome do grupo criado.
		- type: Tipo do grupo criado.

	Retorna:
		- O ID do grupo criado.
\*----------------------------------------------------------------------------*/
stock CreateGroup(groupname[], type = INVALID_GROUP_TYPE)
{
	new nGroupCounter = GetFreeGroupID();
	if(nGroupCounter == INVALID_GROUP_ID)
	{
		print("ERROR: Limite maximo de grupos atingido! (MSi/MSi_groups)");
		return 0;
	}

	g_eGroupData[nGroupCounter][E_GROUP_TYPE] = type;
	format(g_eGroupData[nGroupCounter][E_GROUP_NAME], MAX_GROUP_NAME, "%s", groupname);
	return nGroupCounter;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Alterar o nome de um grupo.

	Params:
		- groupid: ID do grupo.
		- groupname[]: Novo nome para o grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SetGroupName(groupid, groupname[])
{
	format(g_eGroupData[groupid][E_GROUP_NAME], MAX_GROUP_NAME, "%s", groupname);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter o nome de um grupo.

	Params:
		- groupid: ID do grupo.

	Retorna:
		- O nome do grupo.
\*----------------------------------------------------------------------------*/
stock GetGroupName(groupid)
{
	return g_eGroupData[groupid][E_GROUP_NAME];
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter o ID de um grupo atrav�s do nome do grupo.

	Params:
		- groupname[]: Nome do grupo.

	Retorna:
		- O ID do grupo, caso o grupo existir.
		- INVALID_GROUP_ID, caso o grupo N�O existir.
\*----------------------------------------------------------------------------*/
stock GetGroupIDbyName(groupname[])
{
	for (new iii = 1; iii < MAX_GROUPS; iii++)
	{
		if((strcmp(g_eGroupData[iii][E_GROUP_NAME], groupname, true, strlen(groupname)) == 0))
			return iii;
	}
	return INVALID_GROUP_ID;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Alterar o tipo de um grupo.

	Params:
		- groupid: ID do grupo.
		- grouptype: Novo tipo para o grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SetGroupType(groupid, grouptype)
{
	g_eGroupData[groupid][E_GROUP_TYPE] = grouptype;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter o tipo de um grupo.

	Params:
		- groupid: ID do grupo.

	Retorna:
		- O tipo do grupo.
\*----------------------------------------------------------------------------*/
stock GetGroupType(groupid)
{
	return g_eGroupData[groupid][E_GROUP_TYPE];
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Verificar se um jogador pertence a tal grupo.

	Params:
		- playerid: ID do jogador.
		- groupid: ID do grupo.

	Retorna:
		- True se o jogador pertencer ao grupo.
		- False se o jogador n�o pertencer ao grupo.
\*----------------------------------------------------------------------------*/
stock IsPlayerInGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	if (GetPVarInt(playerid, playerGroup))
		return 1;
	return 0;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Adicionar um jogador a um grupo.

	Params:
		- playerid: ID do jogador.
		- groupid: ID do grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock AddPlayerToGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	SetPVarInt(playerid, playerGroup, true);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Remover um jogador de um grupo.

	Params:
		- playerid: ID do jogador.
		- groupid: ID do grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock RemovePlayerFromGroup(playerid, groupid)
{
	new playerGroup[16];
	format(playerGroup, 16, "p_group_%i", groupid);
	DeletePVar(playerid, playerGroup);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Enviar uma mensagem aos jogadores de um grupo.

	Params:
		- playerid: ID do jogador.
		- groupid: ID do grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SendGroupMessage(groupid, color, message[])
{
	for (new slots = GetMaxPlayers(), iii; iii < slots; iii++)
	{
		if (!IsPlayerConnected(iii))
        	continue;

		if (IsPlayerInGroup(iii, groupid))
			SendClientMessage(iii, color, message);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Enviar uma mensagem aos jogadores de um tipo de grupo.

	Params:
		- playerid: ID do jogador.
		- grouptype: ID do tipo grupo.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SendGroupTypeMessage(grouptype, color, message[])
{
	for (new slots = GetMaxPlayers(), iii; iii < slots; iii++)
	{
		if (!IsPlayerConnected(iii))
        	continue;

		for (new ggg = 1; ggg < MAX_GROUPS; ggg++)
		{
			if (IsPlayerInGroup(iii, ggg) && g_eGroupData[ggg][E_GROUP_TYPE] == grouptype)
				SendClientMessage(iii, color, message);	
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter o ID de um grupo livre.

	Params:
		-

	Retorna:
		- O ID do grupo livre, caso tiver.
		- INVALID_GROUP_ID, caso n�o houver grupo livre.
\*----------------------------------------------------------------------------*/
stock GetFreeGroupID()
{
	for (new iii = 1; iii < MAX_GROUPS; iii++)
	{
		if (strlen(g_eGroupData[iii][E_GROUP_NAME]) < 2)
		{
			return iii;
		}
	}
	return INVALID_GROUP_ID;
}