/******************************************************************************
 *				MASTER SERVER INCLUDES - Radars 							  *
 *	@Descrição:																  *
 *		Adiciona funções para criação e manipulação de radares no jogo,		  *
 *		ao jogador passar pelo radar com velocidade acima da permitida		  *
 *		uma callback será chamada, onde você pode decidir o que acontece	  *
 *		ao jogador.															  *
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

#if defined _MSi_radars_included
	#endinput
#endif
#define _MSi_radars_included

/*
native CreateRadar(Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,
				Float:DrawDistance = 200.0, maxspeed = 140, radius = 15.0,
				activated = true);
native SetRadarPosition(radarid, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,
				Float:DrawDistance = 200.0);
native GetRadarPosition(radarid, &Float:Y, &Float:Z, &Float:rX, &Float:rY, &Float:rZ);
native SetRadarActivated(radarid, activated);
native SetRadarRadius(radarid, Float:radius);
native SetRadarMaxSpeed(radarid, maxspeed);
native IsRadarActivated(radarid);
native GetRadarMaxSpeed(radarid);
native GetRadarRadius(radarid);
native DestroyRadar(radarid);
*/

#if !defined MAX_RADARS
	#define MAX_RADARS 32
#endif

#if !defined RADAR_MODEL_ID
	#define RADAR_MODEL_ID 18880
#endif

#define INVALID_RADAR_ID -1

enum E_RADAR_DATA
{
	Float:E_RADAR_POSITION[3],
	Float:E_RADAR_ROTATION[3],
	Float:E_RADAR_DRAWDIST,
	Float:E_RADAR_RADIUS,
	E_RADAR_MAXSPEED,
	E_RADAR_OBJECTID = INVALID_OBJECT_ID,
	E_RADAR_ACTIVATED
}
static g_eRadarData[MAX_RADARS][E_RADAR_DATA];

/*----------------------------------------------------------------------------*\
	Função:
		- Criar um radar.

	Params:
		- X: Coordenada X do radar(objeto!).
		- Y: Coordenada Y do radar(objeto!).
		- Z: Coordenada Z do radar(objeto!).
		
		- rX: Rotação X do radar(objeto!).
		- rY: Rotação Y do radar(objeto!).
		- rZ: Rotação Z do radar(objeto!).

		- DrawDistance: DrawDistance do radar(objeto!).

		- maxspeed: Velocidade máxima permitida do radar.
		- radius: Distância máxima que o radar procurará pelos jogadores.
		- activated: Radar está ativado ou desativado.

	Retorna:
		- O ID do radar criado.
\*----------------------------------------------------------------------------*/
stock CreateRadar(Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,
				Float:DrawDistance = 200.0, maxspeed = 140, Float:radius = 15.0,
				activated = true)
{
	new nRadarCounter = GetFreeRadarID();
	if(nRadarCounter == INVALID_RADAR_ID)
	{
		print("ERROR: Limite maximo de radares atingido! (MSi/MSi_radars)");
		return 0;
	}

	g_eRadarData[nRadarCounter][E_RADAR_POSITION][0] = X;
	g_eRadarData[nRadarCounter][E_RADAR_POSITION][1] = Y;
	g_eRadarData[nRadarCounter][E_RADAR_POSITION][2] = Z;

	g_eRadarData[nRadarCounter][E_RADAR_ROTATION][0] = rX;
	g_eRadarData[nRadarCounter][E_RADAR_ROTATION][1] = rY;
	g_eRadarData[nRadarCounter][E_RADAR_ROTATION][2] = rZ;

	g_eRadarData[nRadarCounter][E_RADAR_DRAWDIST] = DrawDistance;
	g_eRadarData[nRadarCounter][E_RADAR_MAXSPEED] = maxspeed;

	g_eRadarData[nRadarCounter][E_RADAR_RADIUS] 	= radius;
	g_eRadarData[nRadarCounter][E_RADAR_ACTIVATED] 	= activated;

	g_eRadarData[nRadarCounter][E_RADAR_OBJECTID] = CreateObject(RADAR_MODEL_ID, X, Y, Z, rX, rY, rZ, DrawDistance);

	return nRadarCounter;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Destruir um radar.

	Params:
		- radarid: ID do radar que será destruído.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock DestroyRadar(radarid)
{
	if (g_eRadarData[radarid][E_RADAR_OBJECTID] != INVALID_OBJECT_ID)
		DestroyObject(g_eRadarData[radarid][E_RADAR_OBJECTID]);

	g_eRadarData[radarid][E_RADAR_OBJECTID] = INVALID_OBJECT_ID;

	g_eRadarData[radarid][E_RADAR_POSITION][0] = 0.0;
	g_eRadarData[radarid][E_RADAR_POSITION][1] = 0.0;
	g_eRadarData[radarid][E_RADAR_POSITION][2] = 0.0;

	g_eRadarData[radarid][E_RADAR_ROTATION][0] = 0.0;
	g_eRadarData[radarid][E_RADAR_ROTATION][1] = 0.0;
	g_eRadarData[radarid][E_RADAR_ROTATION][2] = 0.0;

	g_eRadarData[radarid][E_RADAR_DRAWDIST] = 0;
	g_eRadarData[radarid][E_RADAR_MAXSPEED] = 0;

	g_eRadarData[radarid][E_RADAR_RADIUS] 		= 0;
	g_eRadarData[radarid][E_RADAR_ACTIVATED]	= false;

	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Alterar posição de um radar.

	Params:
		- radarid: ID do radará.

		- X: Coordenada X do radar(objeto!).
		- Y: Coordenada Y do radar(objeto!).
		- Z: Coordenada Z do radar(objeto!).
		
		- rX: Rotação X do radar(objeto!).
		- rY: Rotação Y do radar(objeto!).
		- rZ: Rotação Z do radar(objeto!).

		- DrawDistance: DrawDistance do radar(objeto!).

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetRadarPosition(radarid, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ,
				Float:DrawDistance = 200.0)
{

	g_eRadarData[radarid][E_RADAR_POSITION][0] = X;
	g_eRadarData[radarid][E_RADAR_POSITION][1] = Y;
	g_eRadarData[radarid][E_RADAR_POSITION][2] = Z;

	g_eRadarData[radarid][E_RADAR_ROTATION][0] = rX;
	g_eRadarData[radarid][E_RADAR_ROTATION][1] = rY;
	g_eRadarData[radarid][E_RADAR_ROTATION][2] = rZ;

	if (g_eRadarData[radarid][E_RADAR_OBJECTID] != INVALID_OBJECT_ID)
		DestroyObject(g_eRadarData[radarid][E_RADAR_OBJECTID]);

	g_eRadarData[radarid][E_RADAR_OBJECTID] = CreateObject(RADAR_MODEL_ID, X, Y, Z, rX, rY, rZ, DrawDistance);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a posição de um radar.

	Params:
		- radarid: ID do radar que terá a posição obtida.

		- X: Coordenada X do objeto do radar, passa por referência.
		- Y: Coordenada X do objeto do radar, passa por referência.
		- Z: Coordenada X do objeto do radar, passa por referência.

		- rX: Rotação do objeto do radar, passa por referência.
		- rY: Rotação do objeto do radar, passa por referência.
		- rZ: Rotação do objeto do radar, passa por referência.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock GetRadarPosition(radarid, &Float:Y, &Float:Z, &Float:rX, &Float:rY, &Float:rZ)
{
	X = g_eRadarData[radarid][E_RADAR_POSITION][0];
	Y = g_eRadarData[radarid][E_RADAR_POSITION][1];
	Z = g_eRadarData[radarid][E_RADAR_POSITION][2];

	rX = g_eRadarData[radarid][E_RADAR_ROTATION][0];
	rY = g_eRadarData[radarid][E_RADAR_ROTATION][1];
	rZ = g_eRadarData[radarid][E_RADAR_ROTATION][2];
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir a radiação de um radar.

	Params:
		- radarid: ID do radar que terá a radiação alterada.
		- radius: Radiação.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetRadarRadius(radarid, Float:radius)
{
	g_eRadarData[radarid][E_RADAR_RADIUS] = radius;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a radiação de um radar.

	Params:
		- radarid: ID do radar que terá a radiação obtida.

	Retorna:
		- A radiação do radar(float).
\*----------------------------------------------------------------------------*/
stock Float:GetRadarRadius(radarid)
{
	return g_eRadarData[radarid][E_RADAR_RADIUS];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir a velocidade máxima de um radar.

	Params:
		- radarid: ID do radar que terá a velocidade max. alterada.
		- maxspeed: Velocidade max.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetRadarMaxSpeed(radarid, maxspeed)
{
	g_eRadarData[radarid][E_RADAR_MAXSPEED] = maxspeed;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a velocidade max. de um radar.

	Params:
		- radarid: ID do radar que terá a velocidade max. obtida.

	Retorna:
		- A velocidade max do radar.
\*----------------------------------------------------------------------------*/
stock GetRadarMaxSpeed(radarid)
{
	return g_eRadarData[radarid][E_RADAR_MAXSPEED];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Alterar estado ativado e desativado do radar.

	Params:
		- radarid: ID do radar que será (des)ativado.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetRadarActivated(radarid, activated)
{
	if(!activated)
		g_eRadarData[radarid][E_RADAR_ACTIVATED] = false;
	else
		g_eRadarData[radarid][E_RADAR_ACTIVATED] = true;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um radar está ativado ou desativado.

	Params:
		- radarid: ID do radar que será verificado.

	Retorna:
		- true, caso o radar esteja ativado.
		- false, caso o radar esteja desativado.
\*----------------------------------------------------------------------------*/
stock IsRadarActivated(radarid)
{
	if(!g_eRadarData[radarid][E_RADAR_ACTIVATED])
		return false;
	return true;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o ID de um radar livre.

	Params:
		-

	Retorna:
		- O ID do radar livre, caso tiver.
		- INVALID_RADAR_ID, cas não houver radar livre.
\*----------------------------------------------------------------------------*/
stock GetFreeRadarID()
{
	for (new iii = 0; iii < MAX_RADARS; iii++)
	{
		if (g_eRadarData[iii][E_RADAR_POSITION][0] == 0.0 && g_eRadarData[iii][E_RADAR_POSITION][1] == 0.0)
		{
			return iii;
		}
	}
	return INVALID_RADAR_ID;
}
// -----------------------------------------------------------------------------
#if defined FILTERSCRIPT
public OnFilterScriptInit()
{
    SetTimer("OnRadarUpdate", 1000, true);
    CallLocalFunction("MSi_radars_OnFilterScriptInit", "");
}
#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit MSi_radars_OnFilterScriptInit
forward OnFilterScriptInit();
#else
public OnGameModeInit()
{
    SetTimer("OnRadarUpdate", 1000, true);
    CallLocalFunction("MSi_radars_OnGameModeInit", "");
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit MSi_radars_OnGameModeInit
forward OnGameModeInit();
#endif
stock _getPlayerSpeed(playerid)
{
	new Float:Vx,
		Float:Vy,
		Float:Vz,
		Float:rtn;
	if(IsPlayerInAnyVehicle(playerid))
		GetVehicleVelocity(GetPlayerVehicleID(playerid),Vx,Vy,Vz);

	rtn = floatsqroot(floatabs(floatpower(Vx + Vy + Vz,2)));
	return floatround(rtn * 100 * 1.61);
}
forward OnPlayerEnterRadar(playerid, radarid, speed);
forward OnRadarUpdate();
public OnRadarUpdate()
{
	for (new slots = GetMaxPlayers(), iii; iii < slots; iii++)
	{
		if (!IsPlayerConnected(iii))
        	continue;

		for (new rrr; rrr < MAX_RADARS; rrr++)
		{
			if (GetPVarInt(iii, "enteredRadar"))
			{
				DeletePVar(iii, "enteredRadar");
				continue;
			}

			if (g_eRadarData[rrr][E_RADAR_POSITION][0] == 0.0 && g_eRadarData[rrr][E_RADAR_POSITION][1] == 0.0)
				continue;

			if (!IsRadarActivated(rrr))
				continue;

			if (!IsPlayerInRangeOfPoint(iii, g_eRadarData[rrr][E_RADAR_RADIUS],  g_eRadarData[rrr][E_RADAR_POSITION][0],  g_eRadarData[rrr][E_RADAR_POSITION][1],  g_eRadarData[rrr][E_RADAR_POSITION][2]))
				continue;

			if (_getPlayerSpeed(iii) < g_eRadarData[rrr][E_RADAR_MAXSPEED])
				continue;

			OnPlayerEnterRadar(iii, rrr, _getPlayerSpeed(iii));
			SetPVarInt(iii, "enteredRadar", 1);
		}
	}
}