/******************************************************************************
 *				MASTER SERVER INCLUDES - Radars 							  *
 *	@Descri��o:																  *
 *		Adiciona fun��es para cria��o e manipula��o de radares no jogo,		  *
 *		ao jogador passar pelo radar com velocidade acima da permitida		  *
 *		uma callback ser� chamada, onde voc� pode decidir o que acontece	  *
 *		ao jogador.															  *
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
	Fun��o:
		- Criar um radar.

	Params:
		- X: Coordenada X do radar(objeto!).
		- Y: Coordenada Y do radar(objeto!).
		- Z: Coordenada Z do radar(objeto!).
		
		- rX: Rota��o X do radar(objeto!).
		- rY: Rota��o Y do radar(objeto!).
		- rZ: Rota��o Z do radar(objeto!).

		- DrawDistance: DrawDistance do radar(objeto!).

		- maxspeed: Velocidade m�xima permitida do radar.
		- radius: Dist�ncia m�xima que o radar procurar� pelos jogadores.
		- activated: Radar est� ativado ou desativado.

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
	Fun��o:
		- Destruir um radar.

	Params:
		- radarid: ID do radar que ser� destru�do.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
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
	Fun��o:
		- Alterar posi��o de um radar.

	Params:
		- radarid: ID do radar�.

		- X: Coordenada X do radar(objeto!).
		- Y: Coordenada Y do radar(objeto!).
		- Z: Coordenada Z do radar(objeto!).
		
		- rX: Rota��o X do radar(objeto!).
		- rY: Rota��o Y do radar(objeto!).
		- rZ: Rota��o Z do radar(objeto!).

		- DrawDistance: DrawDistance do radar(objeto!).

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
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
	Fun��o:
		- Obter a posi��o de um radar.

	Params:
		- radarid: ID do radar que ter� a posi��o obtida.

		- X: Coordenada X do objeto do radar, passa por refer�ncia.
		- Y: Coordenada X do objeto do radar, passa por refer�ncia.
		- Z: Coordenada X do objeto do radar, passa por refer�ncia.

		- rX: Rota��o do objeto do radar, passa por refer�ncia.
		- rY: Rota��o do objeto do radar, passa por refer�ncia.
		- rZ: Rota��o do objeto do radar, passa por refer�ncia.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
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
	Fun��o:
		- Definir a radia��o de um radar.

	Params:
		- radarid: ID do radar que ter� a radia��o alterada.
		- radius: Radia��o.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SetRadarRadius(radarid, Float:radius)
{
	g_eRadarData[radarid][E_RADAR_RADIUS] = radius;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter a radia��o de um radar.

	Params:
		- radarid: ID do radar que ter� a radia��o obtida.

	Retorna:
		- A radia��o do radar(float).
\*----------------------------------------------------------------------------*/
stock Float:GetRadarRadius(radarid)
{
	return g_eRadarData[radarid][E_RADAR_RADIUS];
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Definir a velocidade m�xima de um radar.

	Params:
		- radarid: ID do radar que ter� a velocidade max. alterada.
		- maxspeed: Velocidade max.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
\*----------------------------------------------------------------------------*/
stock SetRadarMaxSpeed(radarid, maxspeed)
{
	g_eRadarData[radarid][E_RADAR_MAXSPEED] = maxspeed;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Obter a velocidade max. de um radar.

	Params:
		- radarid: ID do radar que ter� a velocidade max. obtida.

	Retorna:
		- A velocidade max do radar.
\*----------------------------------------------------------------------------*/
stock GetRadarMaxSpeed(radarid)
{
	return g_eRadarData[radarid][E_RADAR_MAXSPEED];
}

/*----------------------------------------------------------------------------*\
	Fun��o:
		- Alterar estado ativado e desativado do radar.

	Params:
		- radarid: ID do radar que ser� (des)ativado.

	Retorna:
		- Esta fun��o n�o retorna um valor espec�fico.
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
	Fun��o:
		- Verificar se um radar est� ativado ou desativado.

	Params:
		- radarid: ID do radar que ser� verificado.

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
	Fun��o:
		- Obter o ID de um radar livre.

	Params:
		-

	Retorna:
		- O ID do radar livre, caso tiver.
		- INVALID_RADAR_ID, cas n�o houver radar livre.
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