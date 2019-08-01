/******************************************************************************
 *				MASTER SERVER INCLUDES - Zones  							  *
 *	@Função:																  *
 *		Adiciona funções para criação e manipulação de gangzones no jogo,	  *
 *		podendo altera-las dinamicamente e verificar quando um jogador entra  *
 *		e sai de uma zona.						 	                          *
 *	@Legal:																	  *
 *		Este código-fonte está sob os termos de licença da Mozilla Public	  *
 *		License, v. 2.0. Se uma cópia do MPL não for distribuida com este 	  *
 *		arquivo, você pode obter uma em http://mozilla.org/MPL/2.0/			  *
 *																			  *
 *		Os iniciais desenvolvedores deste código é Larceny e Lós.			  *
 *		Códigos criados pelos iniciais desenvolvedores são Copyright (C) 2013 *
 *		Iniciais desenvolvedores.											  *
 *  											Todos os direitos reservados. *
 *	@Versão:																  *
 *		-																	  *
 *	@Autores:																  *
 *		Larceny,															  *
 *		Lós.																  *
 ******************************************************************************/

#include <a_samp>

#if defined _MSi_zones_included
	#endinput
#endif

#define _MSi_zones_included

/*
native GetDynamicZoneArea(zoneid, &Float:minx, &Float:miny, &Float:maxx, &Float:maxy);
native SetDynamicZoneArea(zoneid, Float:minx, Float:miny, Float:maxx, Float:maxy);
native CreateDynamicZone(Float:minx, Float:miny, Float:maxx, Float:maxy, color);
native FlashDynamicZoneForPlayer(playerid, zoneid, color);
native IsDynamicZoneFlashingForPlayer(playerid, zoneid);
native IsDynamicZoneVisibleForPlayer(playerid, zoneid);
native StopFlashDynamicZoneForPlayer(playerid, zoneid);
native ShowDynamicZoneForPlayer(playerid, zoneid);
native HideDynamicZoneForPlayer(playerid, zoneid);
native IsPlayerInDynamicZone(playerid, zoneid);
native FlashDynamicZoneForAll(zoneid, color);
native SetDynamicZoneColor(zoneid, color);
native StopFlashDynamicZoneForAll(zoneid);
native ShowDynamicZoneForAll(zoneid);
native HideDynamicZoneForAll(zoneid);
native GetDynamicZoneColor(zoneid);
native DestroyDynamicZone(zoneid);
native zexist(zoneid);
*/

enum E_ZONE_DATA 
{
	E_GANG_ZONE_ID = INVALID_GANG_ZONE,
	E_GANG_ZONE_COLOR,
	Float:E_GANG_ZONE_MINX,
	Float:E_GANG_ZONE_MINY,
	Float:E_GANG_ZONE_MAXX,
	Float:E_GANG_ZONE_MAXY
}
static g_eZoneData[MAX_GANG_ZONES][E_ZONE_DATA];

/*----------------------------------------------------------------------------*-
Função:
	Trocar o valor entre duas váriaveis.

Params:
	num1 - Primeira variável.
	num2 - Segunda variável.

Retorna:
	-
Notas:
	Troca os valores entre duas variáveis sem uma variavel intermediária.

(c) By Y_Less
-*----------------------------------------------------------------------------*/

#define swap(%1,%2) \
	%1 ^= %2, %2 ^= %1, %1 ^= %2

/*----------------------------------------------------------------------------*\
Função:
	Criar uma gangzone.

Params:
	minx - Minima coordenada X da gangzone
	miny - Minima coordenada Y da gangzone

	maxx - Maxima coordenada X da gangzone
	maxy - Maxima coordenada Y da gangzone
	
	color - Cor da gangzone (Hexadecimal)

Retorna:
	0 caso o limite de gangzones for ultrapasado.
	O id da gangzones criada caso criada com sucesso.
\*----------------------------------------------------------------------------*/
stock CreateDynamicZone(Float:minx, Float:miny, Float:maxx, Float:maxy, color)
{
	new nZoneID = GetFreeZoneID();
	if (nZoneID == INVALID_GANG_ZONE)
	{
		print("ERROR: Limite maximo de gangzones excedido! (MSi/MSi_zones.inc)");
		return 0;
	}

	if(minx > maxx)
		swap(minx, maxx);

	if(miny > maxy)
		swap(miny, maxy);

	g_eZoneData[nZoneID][E_GANG_ZONE_ID] = GangZoneCreate(minx, miny, maxx, maxy);

	g_eZoneData[nZoneID][E_GANG_ZONE_MINX] = minx;
	g_eZoneData[nZoneID][E_GANG_ZONE_MINY] = miny;
	g_eZoneData[nZoneID][E_GANG_ZONE_MAXX] = maxx;
	g_eZoneData[nZoneID][E_GANG_ZONE_MAXY] = maxy;
	g_eZoneData[nZoneID][E_GANG_ZONE_COLOR] = color;
	return nZoneID;
}

/*----------------------------------------------------------------------------*\
Função:
	Destruir uma gangzone.

Params:
	zoneid - ID da gangzone.

Retorna:
	0 caso o ID da gangzone for inválido.
	1 caso a gangzone for destruída com sucesso.
\*----------------------------------------------------------------------------*/
stock DestroyDynamicZone(zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

    GangZoneDestroy(g_eZoneData[zoneid][E_GANG_ZONE_ID]);
    g_eZoneData[zoneid][E_GANG_ZONE_ID] = INVALID_GANG_ZONE;
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Alterar a posição de uma gangzone.

Params:
	zoneid - ID da gangzone.

	minx - Minima coordenada X da gangzone
	miny - Minima coordenada Y da gangzone

	maxx - Maxima coordenada X da gangzone
	maxy - Maxima coordenada Y da gangzone

Retorna:
	0 caso o ID da gangzone for inválido.
	1 caso a pos. da gangzone for alterada com sucesso.
\*----------------------------------------------------------------------------*/
stock SetDynamicZoneArea(zoneid, Float:minx, Float:miny, Float:maxx, Float:maxy)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	if(minx > maxx)
		swap(minx, maxx);

	if(miny > maxy)
		swap(miny, maxy);

    GangZoneDestroy(g_eZoneData[zoneid][E_GANG_ZONE_ID]);

	g_eZoneData[zoneid][E_GANG_ZONE_MINX] = minx;
	g_eZoneData[zoneid][E_GANG_ZONE_MINY] = miny;
	g_eZoneData[zoneid][E_GANG_ZONE_MAXX] = maxx;
	g_eZoneData[zoneid][E_GANG_ZONE_MAXY] = maxy;
	g_eZoneData[zoneid][E_GANG_ZONE_ID] = GangZoneCreate(minx, miny, maxx, maxy);
	
	new str_zone_id[14];
	for (new i; i < MAX_PLAYERS; i++)
	{
		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		if (GetPVarInt(i, str_zone_id) == 1)
		{
			GangZoneHideForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID]);
			GangZoneShowForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID], g_eZoneData[zoneid][E_GANG_ZONE_COLOR]);
		}
	}
	
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Obter as coordenadas da area de uma gangzone.

Params:
	zoneid - ID da gangzone para obter as coordenadas

	minx - Minima coordenada X da gangzone, passada por ref.
	miny - Minima coordenada Y da gangzone, passada por ref.
	maxx - Maxima coordenada X da gangzone, passada por ref.
	maxy - Maxima coordenada Y da gangzone, passada por ref.

Retorna:
	0 caso a gangzone for inválida.
	1 caso os valores forem passados.
\*----------------------------------------------------------------------------*/
stock GetDynamicZoneArea(zoneid, &Float:minx, &Float:miny, &Float:maxx, &Float:maxy)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	minx = g_eZoneData[zoneid][E_GANG_ZONE_MINX];
	miny = g_eZoneData[zoneid][E_GANG_ZONE_MINY];
	maxx = g_eZoneData[zoneid][E_GANG_ZONE_MAXX];
	maxy = g_eZoneData[zoneid][E_GANG_ZONE_MAXY];
	return zoneid;
}

/*----------------------------------------------------------------------------*\
Função:
	Mostrar uma gangzone para um jogador.

Params:
	playerid - ID do jogador que verá a gangzone
	zoneid - ID da gangzone que será mostrada ao jogador

Retorna:
	-1 caso o id do jogador for inválido.
	0 caso o id da gangzone for inválida.
	1 caso a gangzone for mostrada para o jogador.
\*----------------------------------------------------------------------------*/
stock ShowDynamicZoneForPlayer(playerid, zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	if (!IsPlayerConnected(playerid) || playerid == INVALID_PLAYER_ID)
		return -1;

    GangZoneShowForPlayer(playerid, g_eZoneData[zoneid][E_GANG_ZONE_ID], g_eZoneData[zoneid][E_GANG_ZONE_COLOR]);

	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
	SetPVarInt(playerid, str_zone_id, 1);
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Ocultar uma gangzone para um jogador.

Params:
	playerid - ID do jogador que será oculta a gangzone
	zoneid -   ID da gangzone que será ocultada ao jogador

Retorna:
	-1 caso o id do jogador for inválido.
	0 caso o id da gangzone for inválida.
	1 caso a gangzone for ocultada para o jogador.
\*----------------------------------------------------------------------------*/
stock HideDynamicZoneForPlayer(playerid, zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	if (!IsPlayerConnected(playerid) || playerid == INVALID_PLAYER_ID)
		return -1;

    GangZoneHideForPlayer(playerid, g_eZoneData[zoneid][E_GANG_ZONE_ID]);

	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
	DeletePVar(playerid, str_zone_id);
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Mostrar uma gangzone para todos os jogadores.

Params:
	zoneid - ID da gangzone que será mostrada.

Retorna:
	0 caso o id da gangzone for inválida.
	1 caso a gangzone for mostrada a todos.
\*----------------------------------------------------------------------------*/
stock ShowDynamicZoneForAll(zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	new str_zone_id[14];
    for (new i; i < MAX_PLAYERS; i++)
    {
    	if (!IsPlayerConnected(i))
			continue;

		GangZoneShowForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID],
			g_eZoneData[zoneid][E_GANG_ZONE_COLOR]);

		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		SetPVarInt(i, str_zone_id, 1);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Ocultar uma gangzone para todos.

Params:
	zoneid - ID da gangzone que será ocultada.

Retorna:
	0 caso o id da gangzone for inválida.
	1 caso a gangzone for ocultada a todos.
\*----------------------------------------------------------------------------*/
stock HideDynamicZoneForAll(zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	new str_zone_id[14];
    for (new i; i < MAX_PLAYERS; i++)
    {
    	if(!IsPlayerConnected(i))
			continue;

		GangZoneHideForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID]);

		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		DeletePVar(i, str_zone_id);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Esta função pisca uma dynamic gangzone para todos

Params:
	zoneid - ID da gangzone que irá piscar
	color - Segunda cor na qual a gangzone irá piscar.

Retorna:
	0 caso o id da gangzone for inválido.
	1 caso a gangzone for piscada a todos.
\*----------------------------------------------------------------------------*/
stock FlashDynamicZoneForAll(zoneid, color)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	new str_zone_id[14];
    for (new i; i < MAX_PLAYERS; i++)
    {
    	if(!IsPlayerConnected(i))
			continue;

		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		if (GetPVarInt(i, str_zone_id) == 1)
		{
			GangZoneFlashForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID], color);
			format(str_zone_id, sizeof str_zone_id, "fszone_%i", zoneid);
			SetPVarInt(i, str_zone_id, 1);
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	- Parar de piscar uma gangzone para todos

Params:
	zoneid - ID da gangzone que parará de piscar

Retorna:
	0 caso a gangzone for inválida.
	1 caso a gangzone for piscada a todos.
\*----------------------------------------------------------------------------*/
stock StopFlashDynamicZoneForAll(zoneid)
{
	if (g_eZoneData[zoneid][E_GANG_ZONE_ID] == INVALID_GANG_ZONE)
		return 0;

	new str_zone_id[14];
    for (new i; i < MAX_PLAYERS; i++)
    {
    	if(!IsPlayerConnected(i))
			continue;

		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		if (GetPVarInt(i, str_zone_id) == 1)
		{
			GangZoneStopFlashForPlayer(i, g_eZoneData[zoneid][E_GANG_ZONE_ID]);
			format(str_zone_id, sizeof str_zone_id, "fszone_%i", zoneid);
			DeletePVar(i, str_zone_id);
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Piscar uma gangzone para um jogador

Params:
	playerid - ID do jogador que verá a gangzone piscar
	zoneid - ID da gangzone que irá piscar
	color - Segunda cor na qual a gangzone irá piscar

Retorna:
	-1 caso o jogador for inválido.
	0 caso a gangzone for inválida.
	1 caso a zona for piscada.
\*----------------------------------------------------------------------------*/
stock FlashDynamicZoneForPlayer(playerid, zoneid, color)
{
	if (g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ] == INVALID_GANG_ZONE)
		return 0;

	if(!IsPlayerConnected(playerid) || playerid == INVALID_PLAYER_ID)
		return -1;

	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
	if (GetPVarInt(playerid, str_zone_id) == 1) {
		GangZoneFlashForPlayer(playerid,
			g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ],
			color);
		format(str_zone_id, sizeof str_zone_id, "fszone_%i", zoneid);
		SetPVarInt(playerid, str_zone_id, 1);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Parar de piscar uma gangzone para um jogador

Params:
	playerid - ID do jogador que verá a gangzone parar de piscar
	zoneid - ID da gangzone que irá parar de piscar

Retorna:
	-1 caso o jogador for inválido.
	0 caso a gangzone for inválida.
	1 caso parar de piscar.
\*----------------------------------------------------------------------------*/
stock StopFlashDynamicZoneForPlayer(playerid, zoneid)
{
	if (g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ] == INVALID_GANG_ZONE)
		return 0;

	if(!IsPlayerConnected(playerid) || playerid == INVALID_PLAYER_ID)
		return -1;

	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
	if (GetPVarInt(playerid, str_zone_id) == 1) {
		GangZoneStopFlashForPlayer(playerid,
			g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ]);
		format(str_zone_id, sizeof str_zone_id, "fszone_%i",
			zoneid);
		DeletePVar(playerid, str_zone_id);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Definir a cor de uma gangzone

Params:
	zoneid - ID da gangzone que irá mudar de cor
	color - Nova cor da gangzone (hexadecimal)

Retorna:
	0 caso a gangzone for inválida.
	1 caso mudar a cor da gangzone
\*----------------------------------------------------------------------------*/
stock SetDynamicZoneColor(zoneid, color)
{
	if (g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ] == INVALID_GANG_ZONE)
		return 0;

	g_eZoneData[ zoneid ][ E_GANG_ZONE_COLOR ] = color;
	new str_zone_id[14];
    for (new i; i < MAX_PLAYERS; i++) {
    	if(!IsPlayerConnected(i))
			continue;

		format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
		if (GetPVarInt(i, str_zone_id) == 1) {
			GangZoneHideForPlayer(i,
				g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ]);
			GangZoneShowForPlayer(i,
				g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ],
				g_eZoneData[ zoneid ][ E_GANG_ZONE_COLOR ]);
		}
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Obter a cor de uma gangzone.

Params:
	zoneid - ID da gangzone que irá obter a cor

Retorna:
	0 caso a gangzone for inválida.
	A cor da gangzone caso executada com sucesso.
\*----------------------------------------------------------------------------*/
stock GetDynamicZoneColor(zoneid)
{
	if (g_eZoneData[ zoneid ][ E_GANG_ZONE_ID ] == INVALID_GANG_ZONE)
		return 0;

	return g_eZoneData[ zoneid ][ E_GANG_ZONE_COLOR ];
}

/*----------------------------------------------------------------------------*\
Função:
	Esta função retorna se uma zona é visível para um jogador.

Params:
	playerid - ID do jogador para verificar se pode ver a zona
	zoneid - ID da gangzone para verificar se o jogador pode ve-la

Retorna:
	0 se o jogador não puder ver a zona.
	1 se o jogador puder ver a zona.
\*----------------------------------------------------------------------------*/
stock IsDynamicZoneVisibleForPlayer(playerid, zoneid)
{
	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "vszone_%i", zoneid);
	return (!GetPVarInt(playerid, str_zone_id)) ? 0 : 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Verificar se uma zona está piscando para um jogador.

Params:
	playerid - ID do jogador para verificar se a zona está piscando
	zoneid - ID da gangzone para verificar se o jogador ve piscando

Retorna:
	0 se a zona não estiver picando para o jogador.
	1 se a zona estiver picando para o jogador.
\*----------------------------------------------------------------------------*/
stock IsDynamicZoneFlashingForPlayer(playerid, zoneid)
{
	new str_zone_id[14];
	format(str_zone_id, sizeof str_zone_id, "fszone_%i", zoneid);
	return (!GetPVarInt(playerid, str_zone_id)) ? 0 : 1;
}

/*----------------------------------------------------------------------------*\
Função:
	- Checar se um jogador está dentro de uma gangzone

Params:
	playerid - ID do jogador para verificar se está na zona
	zoneid - ID da gangzone para verificar se o jogador está na zona

Retorna:
	0 se o jogador não estiver na zona.
	1 se o jogador estiver na zona.
\*----------------------------------------------------------------------------*/
stock IsPlayerInDynamicZone(playerid, zoneid)
{
    new
		Float:x,
		Float:y,
		Float:z;

    GetPlayerPos(playerid, x, y, z);
    if (x > g_eZoneData[ zoneid ][ E_GANG_ZONE_MINX ] &&
    	x < g_eZoneData[ zoneid ][ E_GANG_ZONE_MAXX ] &&
    	y > g_eZoneData[ zoneid ][ E_GANG_ZONE_MINY ] &&
    	y < g_eZoneData[ zoneid ][ E_GANG_ZONE_MAXY ]) return 1;
    return 0;
}

/*----------------------------------------------------------------------------*\
Função:
	Checar se uma gangzone existe

Params:
	zoneid - ID da gangzone para verificar se existe

Retorna:
	0 se a gangzone não existir.
	1 se a gangzone existir.
\*----------------------------------------------------------------------------*/
stock zexist(zoneid)
{
	return (!g_eZoneData[zoneid][E_GANG_ZONE_ID]) ? 0 : 1;
}

/*----------------------------------------------------------------------------*\
Função:
	- Procurar por IDS de gangzones livres.

Params:
	-

Retorna:
	- O primeiro id de uma gangzone livre
	- INVALID_GANG_ZONE caso não houver espaço para mais gangzones
\*----------------------------------------------------------------------------*/
stock GetFreeZoneID()
{
	for (new z = 0; z < MAX_GANG_ZONES; z++)
		if (g_eZoneData[ z ][ E_GANG_ZONE_ID ] == INVALID_GANG_ZONE)
			return z;
	return INVALID_GANG_ZONE;
}

/*----------------------------------------------------------------------------*\
Função:
	Fazer uma checagem a todo segundo para verificar se algum jogador
	entrou ou saiu de alguma zona.

Params:
	-

Retorna:
	-

Notas:
	Esta callback é chamada a cada segundo!
\*----------------------------------------------------------------------------*/
forward dzones_Check();
public dzones_Check()
{
	new str_zone_id[14];
	for (new i = 0; i < MAX_PLAYERS; i++)
	{
		if(!IsPlayerConnected(i))
			continue;

		for (new z = 0; z < MAX_GANG_ZONES; z++)
		{
			format(str_zone_id, sizeof str_zone_id, "etzone_%i", z);
			if (IsPlayerInDynamicZone(i, z) && GetPVarInt(i, str_zone_id) == 0)
			{
				CallLocalFunction("OnPlayerEnterDynamicZone", "ii", i, str_zone_id);
				SetPVarInt(i, str_zone_id, 1);
			}
			else if (!IsPlayerInDynamicZone(i, z) && GetPVarInt(i, str_zone_id) == 1)
			{
				CallLocalFunction("OnPlayerExitDynamicZone", "ii", i, str_zone_id);
				DeletePVar(i, str_zone_id);
			}
		}
	}
	return 1;
}
// -----------------------------------------------------------------------------
#if defined FILTERSCRIPT
	public OnFilterScriptInit()
	{
		for (new z = 0; z < MAX_GANG_ZONES; z++)
		{
			g_eZoneData[ z ][ E_GANG_ZONE_ID ] = INVALID_GANG_ZONE;
		}
		SetTimer("dzones_Check", 1000, true);
		return CallLocalFunction("dzones_OnFilterScriptInit", "");
	}
	#if defined _ALS_OnFilterScriptInit
		#undef OnFilterScriptInit
	#else
		#define _ALS_OnFilterScriptInit
	#endif
	#define OnFilterScriptInit dzones_OnFilterScriptInit
	forward dzones_OnFilterScriptInit();
	forward OnPlayerEnterDynamicZone(playerid, zoneid);
	forward OnPlayerExitDynamicZone(playerid, zoneid);
#else
	public OnGameModeInit()
	{
		for (new z = 0; z < MAX_GANG_ZONES; z++)
		{
			g_eZoneData[ z ][ E_GANG_ZONE_ID ] = INVALID_GANG_ZONE;
		}
		SetTimer("dzones_Check", 1000, true);
		return CallLocalFunction("dzones_OnGameModeInit", "");
	}
	#if defined _ALS_OnGameModeInit
		#undef OnGameModeInit
	#else
		#define _ALS_OnGameModeInit
	#endif
	#define OnGameModeInit dzones_OnGameModeInit
	forward dzones_OnGameModeInit();
	forward OnPlayerEnterDynamicZone(playerid, zoneid);
	forward OnPlayerExitDynamicZone(playerid, zoneid);
#endif
#undef swap