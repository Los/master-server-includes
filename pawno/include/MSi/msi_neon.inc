/******************************************************************************
 *				MASTER SERVER INCLUDES - Neon 								  *
 *	@Descrição:																  *
 *		Adiciona funções para de criar e anexar objetos luminosos à veículos  *
 *		como se fossem neons.												  *
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

#if defined _MSi_neon_included
	#endinput
#endif
#define _MSi_neon_included

/*
native AttachNeonToVehicle(vehicleid, neonid);
native RemoveBuzzerFromVehicle(vehicleid);
native RemoveNeonFromVehicle(vehicleid);
native IsVehicleUsingBuzzer(vehicleid);
native GetVehicleNeonColor(vehicleid);
native IsVehicleUsingNeon(vehicleid);
*/

#define NEON_COLOR_BLUE 	(0)
#define NEON_COLOR_PINK 	(1)
#define NEON_COLOR_YELLOW 	(2)
#define NEON_COLOR_GREEN	(3)
#define NEON_COLOR_RED		(4)
#define NEON_COLOR_WHITE	(5)
#define NEON_COLOR_POLICE	(6)

#define GetVehicleNeonColor(%0) 	g_sNeonColorName[%0]
#define IsVehicleUsingNeon(%0) 		IsValidObject(g_oNeon1[%0])
#define IsVehicleUsingBuzzer(%0) 	IsValidObject(g_oNeon3[%0])

new g_oNeon1[MAX_VEHICLES] = {INVALID_OBJECT_ID, ...};
new g_oNeon2[MAX_VEHICLES] = {INVALID_OBJECT_ID, ...};
new g_oNeon3[MAX_VEHICLES] = {INVALID_OBJECT_ID, ...};
new g_sNeonColorName[MAX_VEHICLES][10] = "Nenhum";

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um veículo é uma moto.

	Params:
		- vehicleid: ID do veículo a ser verificado.

	Retorna:
		- true, caso o veículo for uma moto.
		- false, caso o veículo não for uma moto.
\*----------------------------------------------------------------------------*/
stock _isVehicleABike(vehicleid)
{   
	switch (GetVehicleModel(vehicleid)) {
		case 461..463, 448, 468, 471, 481, 509, 510, 521..523, 581, 586: return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Anexar um neon a um veículo.

	Params:
		- vehicleid: ID do veículo.
		- neonid: ID da cor do neon a ser anexado.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock AttachNeonToVehicle(vehicleid, neonid)
{
    switch(neonid)
    {
		case NEON_COLOR_BLUE:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18648, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18648, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18648, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Azul";
			return 1;
		}
		case NEON_COLOR_PINK:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18651, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18651, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18651, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Rosa";
			return 1;
		}
		case NEON_COLOR_YELLOW:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18650, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18650, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18650, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Amarelo";
			return 1;
		}
		case NEON_COLOR_GREEN:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18649, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18649, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18649, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Verde";
			return 1;
		}
		case NEON_COLOR_RED:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18647, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18647, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18647, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Vermelho";
			return 1;
		}
		case NEON_COLOR_WHITE:
		{
			if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
			if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

			if(_isVehicleABike(vehicleid))
			{
				g_oNeon1[vehicleid] = CreateObject(18652, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, 0.0, 0.0, -0.70, 0.0, 0.0, 0.0);
				g_oNeon2[vehicleid] = INVALID_OBJECT_ID;
			}
			else
			{
				g_oNeon1[vehicleid] = CreateObject(18652, 0, 0, 0, 0, 0, 0);
				g_oNeon2[vehicleid] = CreateObject(18652, 0, 0, 0, 0, 0, 0);
			}

			AttachObjectToVehicle(g_oNeon1[vehicleid], vehicleid, -0.8, 0.0, -0.70, 0.0, 0.0, 0.0); 
			AttachObjectToVehicle(g_oNeon2[vehicleid], vehicleid, 0.8, 0.0, -0.70, 0.0, 0.0, 0.0);

			g_sNeonColorName[vehicleid] = "Branco";
			return 1;
		}
		case NEON_COLOR_POLICE:
		{
			if(_isVehicleABike(vehicleid))
			{
				g_oNeon3[vehicleid] = CreateObject(18646, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon3[vehicleid], vehicleid, 0.014999, 0.724999, 0.669999, 0.0, 0.0, 0.0);
			}
			else
			{
				g_oNeon3[vehicleid] = CreateObject(18646, 0, 0, 0, 0, 0, 0);
				AttachObjectToVehicle(g_oNeon3[vehicleid], vehicleid, -0.5, -0.2, 0.8, 2.0, 2.0, 3.0); 
			}
			return 1;
		}
		default:
		{
			print("ERROR: Cor do neon invalida! (MSi/MSi_neon.inc)");
		}
    }
    return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Remover um neon de um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock RemoveNeonFromVehicle(vehicleid)
{
    if (IsValidObject(g_oNeon1[vehicleid])) DestroyObject(g_oNeon1[vehicleid]);
    if (IsValidObject(g_oNeon2[vehicleid])) DestroyObject(g_oNeon2[vehicleid]);

	g_oNeon1[vehicleid] = INVALID_OBJECT_ID;
	g_oNeon2[vehicleid] = INVALID_OBJECT_ID;

	g_sNeonColorName[vehicleid] = "Nenhum";
    return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Remover uma sirene de um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock RemoveBuzzerFromVehicle(vehicleid)
{
    if (IsValidObject(g_oNeon3[vehicleid])) DestroyObject(g_oNeon3[vehicleid]);

	g_oNeon3[vehicleid] = INVALID_OBJECT_ID;
    return 1;
}