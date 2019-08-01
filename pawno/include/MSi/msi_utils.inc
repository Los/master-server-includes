/******************************************************************************
 *				MASTER SERVER INCLUDES - Utils	 							  *
 *	@Descrição:																  *
 *		Adiciona funções e macros para simplificar e ajudar a escrever códigos*
 *		mais rapidamente.													  *
 *	@Legal:																	  *
 *		Este código-fonte está sob os termos de licença da Mozilla Public	  *
 *		License, v. 2.0. Se uma cópia do MPL não for distribuida com este 	  *
 *		arquivo, você pode obter uma em http://mozilla.org/MPL/2.0/			  *
 *																			  *
 *		Os iniciais desenvolvedores deste código são Larceny e Lós.			  *
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

#if defined _msi_utils_included
	#endinput
#endif

#define _msi_utils_included

#if !defined isnull
    #define isnull(%1) \
                ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define SetVehicleInterior LinkVehicleToInterior

#define INVALID_SEAT_ID -1

forward _msi_update_checkpoint ( playerid, targetid );

/*
native GetPlayerNameEx(playerid);
native GetPlayerArmourEx(playerid);
native GetPlayerHealthEx(playerid);
native GetPlayerFacingAngleEx(playerid);
native GetVehicleZAngleEx(vehicleid);
native IsPlayerSpectating(playerid);
native IsAValidSkin(skinid);
native GetFreeVehicleSeat(vehicleid);
native GetVehicleDriver(vehicleid);
native GetDistanceBetweenPlayers(playerid,targetid);
native CreateCheckpointOnPlayer(playerid,targetid,follow,update_time);
native GetPlayerDistanceFromVehicle(playerid,vehicleid);
native IsPlayerInRangeOfVehicle(playerid,vehicleid,Float:radius);
native GetPlayerIpEx(playerid);
native GetPlayerWeaponName(playerid);
native GetWeaponNameEx(weaponid);
native ClearClientChat(playerid);
native ClearClientChatToAll();
native SetPlayerMoney(playerid,money);
native SetPlayerPosEx(playerid,Float:x,Float:y,Float:z,Float:a);
native GivePlayerWantedLevel(playerid,level);
native FreezePlayer(playerid,time=5000);
native RemovePlayerWeapon(playerid,weaponid);
native GetVehicleHealthEx(vehicleid);
native RemovePlayerSlotWeapon(playerid,slotid);
native IsVehicleOccupied(vehicleid);
native TeleportPlayerToVehicle(playerid,vehicleid);
native TeleportPlayerToPlayer(playerid,targetid);
native IsPlayerDriver(playerid);
native IsPlayerPassenger(playerid);
native IsPlayerSwimming(playerid);
native FlipVehicle(vehicleid);
native GetVehicleName(vehicleid);
native GetVehicleEngineStatus(vehicleid);
native IsVehicleLocked(vehicleid);
native LockVehicle(vehicleid);
native UnlockVehicle(vehicleid);
native SendAdminMessage(color,constmessage[]);
native OnPlayerUnfreeze(playerid);
*/

/*----------------------------------------------------------------------------*\
	Função:
		- Cria um checkpoint para tal jogador em outro jogador, seguindo.

	Params:
		- playerid: ID do jogador que vai ver o checkpoint.
		- targetid: ID do jogador que vai ter o checkpoint criado.

	Retorna:
		- Timer reiniciando o processo
\*----------------------------------------------------------------------------*/
public _msi_update_checkpoint ( playerid, targetid )
{
	new
		Float: flo_pos [ 3 ];

	GetPlayerPos ( targetid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
	SetPlayerCheckpoint ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return SetTimerEx ( "_msi_update_checkpoint", 1000, false, "dd", playerid, targetid );
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o nome do jogador sem necessidade de uma array intermediária.

	Params:
		- playerid: ID do jogador que terá o nome obtido

	Retorna:
		- O nome do jogador (string) caso o id for válido.
\*----------------------------------------------------------------------------*/
stock GetPlayerNameEx ( playerid )
{
    new
    	str_player_name [ MAX_PLAYER_NAME ];

    GetPlayerName ( playerid, str_player_name, MAX_PLAYER_NAME );

    return str_player_name;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o valor da saúde do colete do jogador, sem necessidade de uma
		variável intermediária.

	Params:
		- playerid: ID do jogador que terá o valor do colete obtido

	Retorna:
		- 0 caso o id do jogador for inválido.
		- A saúde do colete (float) caso o id for válido.
\*----------------------------------------------------------------------------*/
stock Float: GetPlayerArmourEx ( playerid )
{
	new
		Float: flo_player_armour;

	GetPlayerArmour ( playerid, flo_player_armour );

	return flo_player_armour;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o valor da saúde do jogador, sem necessidade de uma
		variável intermediária.

	Params:
		- playerid: ID do jogador que terá o valor da vida obtida

	Retorna:
		- 0 caso o id do jogador for inválido.
		- A saúde (float) caso o id for válido.
\*----------------------------------------------------------------------------*/
stock Float: GetPlayerHealthEx ( playerid )
{
	new	
		Float: flo_player_health;

	GetPlayerHealth ( playerid, flo_player_health );

	return flo_player_health;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o ângulo do jogador, sem necessidade de uma
		variável intermediária.

	Params:
		- playerid: ID do jogador que terá o valor do ângulo obtido

	Retorna:
		- 0 caso o id do jogador for inválido.
		- O ângulo (float) caso o id for válido.
\*----------------------------------------------------------------------------*/
stock Float: GetPlayerFacingAngleEx ( playerid )
{
	new
		Float: flo_player_angle;

	GetPlayerFacingAngle ( playerid, flo_player_angle );

	return flo_player_angle;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o ângulo Z do veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- O ângulo do veículo (float).
\*----------------------------------------------------------------------------*/
stock Float: GetVehicleZAngleEx ( vehicleid )
{
	new
		Float: flo_vehicle_angle;

	GetVehicleZAngle ( vehicleid, flo_vehicle_angle );

	return flo_vehicle_angle;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um jogador está de espectador.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- 1 se o jogador estiver de espectador.
		- 0 se o jogador não estiver.
\*----------------------------------------------------------------------------*/
stock IsPlayerSpectating ( playerid ) {
	return ( GetPlayerState ( playerid ) == PLAYER_STATE_SPECTATING ) ? 1 : 0; 
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se é uma skin válida.

	Params:
		- skin: ID da skin.

	Retorna:
		- 1 se a skin for válida.
		- 0 se a skin for inválida.
\*----------------------------------------------------------------------------*/
stock IsAValidSkin ( skinid ) {
	return (skinid < 0 || skinid > 299 || skinid == 74 ) ? 0 : 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém próximo banco disponível de um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- O ID do assento caso houver disponível.
		- INVALID_SEAT_ID (ou -1) caso não houver bancos disponíveis.
\*----------------------------------------------------------------------------*/
stock GetFreeVehicleSeat ( vehicleid )
{
	new
		bool: boo_vehicle_seats [ 5 ];

	for ( new slots = GetMaxPlayers ( ), i; i < slots; i++ )
		if ( IsPlayerInVehicle ( i, vehicleid ) )
			if ( GetPlayerVehicleSeat ( i ) != 128 )
				boo_vehicle_seats [ GetPlayerVehicleSeat ( i ) ] = true;

	for ( new seat; seat < sizeof boo_vehicle_seats; seat++ )
		if ( boo_vehicle_seats [ seat ] )
			continue;

		return seat;

	return INVALID_SEAT_ID;
}



/*----------------------------------------------------------------------------*\
	Função:
		- Obter o motorista de um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- O ID do jogador que estiver dirigindo o veículo.
		- INVALID_PLAYER_ID caso não tiver motorista.
\*----------------------------------------------------------------------------*/
stock GetVehicleDriver ( vehicleid )
{
	for ( new slots = GetMaxPlayers( ), i; i < slots; i++ )
		if ( !IsPlayerConnected ( playerid ) )
			continue;

		if ( IsPlayerInVehicle ( playerid, vehicleid ) )
			return i;

	return INVALID_PLAYER_ID;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a distância entre dois jogadores.

	Params:
		- playerid: ID do jogador 1.
		- targetid: ID do jogador 2.

	Retorna:
		- A distância (float) entre os dois jogadores.
\*----------------------------------------------------------------------------*/
stock Float: GetDistanceBetweenPlayers ( playerid, targetid )
{
	new
		Float: flo_pos [ 3 ];

	GetPlayerPos ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return GetPlayerDistanceFromPoint ( targetid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
}

/*----------------------------------------------------------------------------*\
	Função:
		- Cria um checkpoint para tal jogador em outro jogador, seguindo
		ou não.

	Params:
		- playerid: ID do jogador que vai ver o checkpoint.
		- targetid: ID do jogador que vai ter o checkpoint criado.
		- follow: 1 (Checkpoint Segue) - 2 (Checkpoint Fixo)
		- update_time: tempo de atualização do checkpoint em milisegundos
		(0 caso não utilizar)

	Retorna:
		- 1
\*----------------------------------------------------------------------------*/
stock Float: CreateCheckpointOnPlayer ( playerid, targetid, follow, update_time )
{
	new
		Float: flo_pos [ 3 ];

	GetPlayerPos ( targetid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	switch ( follow )
	{
		case 1:
		{
			SetPlayerCheckpoint ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
			SetTimerEx ( "_msi_update_checkpoint", 1000, false, "dd", playerid, targetid );
		}
		case 2: SetPlayerCheckpoint ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
	}

	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a distância entre um jogador e um veículo.

	Params:
		- playerid: ID do jogador.
		- vehicleid: ID do veículo.

	Retorna:
		- A distância (float) entre o jogador e o veículo.
\*----------------------------------------------------------------------------*/
stock Float: GetPlayerDistanceFromVehicle ( playerid, vehicleid )
{
	new
		Float: flo_pos [ 3 ];

	GetPlayerPos ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return GetVehicleDistanceFromPoint(vehicleid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se o jogador está próximo de um veículo, dentro de uma
		determinada radiação.

	Params:
		- playerid: ID do jogador.
		- vehicleid: ID do veículo.
		- radius: Radiação máxima (float) a ser checada.

	Retorna:
		- 1 se o jogador estiver dentro da radiação do veículo.
		- 0 se o jogador não estiver.
\*----------------------------------------------------------------------------*/
stock IsPlayerInRangeOfVehicle ( playerid, vehicleid, Float: radius )
{
	new
		Float: flo_pos [ 3 ];

	GetVehiclePos ( vehicleid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return IsPlayerInRangeOfPoint ( playerid, radius, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o IP de um jogador, sem a necessidade de uma variável
		intermediária.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- O ip do jogador (string).
\*----------------------------------------------------------------------------*/
stock GetPlayerIpEx ( playerid )
{
	new
		str_player_ip [ 18 ];

	GetPlayerIp ( playerid, str_player_ip, sizeof str_player_ip );

    return str_player_ip;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o nome da arma do jogador.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- O nome da arma do jogador (string).
\*----------------------------------------------------------------------------*/
stock GetPlayerWeaponName ( playerid )
{
    new
    	str_weapon_name [ 21 ];

    GetWeaponName ( GetPlayerWeapon ( playerid ), str_weapon_name, sizeof str_weapon_name );

	switch ( GetPlayerWeapon ( playerid ) )
	{
		case 0: str_weapon_name = "Nenhuma";
		case 18: str_weapon_name = "Molotov Cocktail";
		case 44: str_weapon_name = "Night Vis Goggles";
		case 45: str_weapon_name = "Thermal Goggles";
	}

    return str_weapon_name;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o nome de uma arma sem necessidade de uma variável
		intermediária.

	Params:
		- weaponid: ID da arma.

	Retorna:
		- 'desconhecida' caso o id da arma for inválido.
		- O nome da arma (string) caso o id for válido.
\*----------------------------------------------------------------------------*/
stock GetWeaponNameEx ( weaponid )
{
    new
    	str_weapon_name [ 21 ];

    GetWeaponName ( weaponid, str_weapon_name, sizeof str_weapon_name );

	switch ( GetPlayerWeapon ( playerid ) )
	{
		case 0: str_weapon_name = "Nenhuma";
		case 18: str_weapon_name = "Molotov Cocktail";
		case 44: str_weapon_name = "Night Vis Goggles";
		case 45: str_weapon_name = "Thermal Goggles";
	}

    return str_weapon_name;
}


/*----------------------------------------------------------------------------*\
	Função:
		- Limpar o chat de um jogador.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock ClearClientChat ( playerid )
{
	for ( new i = 0; i < 100; i++ )
		SendClientMessage ( playerid, -1, " " );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Limpar o chat de todos os jogadores.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock ClearClientChatToAll ( )
{
	for ( new i = 0; i < 100; i++ )
		SendClientMessageToAll ( -1, " " );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir o dinheiro de um jogador.

	Params:
		- playerid: ID do jogador.
		- money: Quantia de dinheiro.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetPlayerMoney ( playerid, money )
{
	ResetPlayerMoney ( playerid );
	GivePlayerMoney ( playerid, money );
	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir a posição e ângulo do jogador.

	Params:
		- playerid: ID do jogador.
		- Floatx: Posição X.
		- Floaty: Posição Y.
		- Floatz: Posição Z.
		- Floata: Ângulo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetPlayerPosEx ( playerid, Float: x, Float: y, Float: z, Float: a )
{
	SetPlayerPos ( playerid, x, y, z );
	SetPlayerFacingAngle ( playerid, a );
	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Acrescentar nível de procurar a um jogador.

	Params:
		- playerid: ID do jogador.
		- level: Nível de procurado a ser acrescentado.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock GivePlayerWantedLevel ( playerid, level )
{
	if ( level + GetPlayerWantedLevel ( playerid ) > 6 )
		return SetPlayerWantedLevel ( playerid, 6 );

	SetPlayerWantedLevel ( playerid, GetPlayerWantedLevel ( playerid ) + level );
	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Congelar um jogador por um período de tempo.

	Params:
		- playerid: ID do jogador.
		- time: Tempo em que o jogador ficará congelado.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock FreezePlayer ( playerid, time = 5000)
{
	TogglePlayerControllable(playerid, false);

	if ( GetPVarInt ( playerid, "FreezeTimer" ) != 0 )
		KillTimer ( GetPVarInt ( playerid, "FreezeTimer" ) );

	SetPVarInt ( playerid, "FreezeTimer", time );

	SetTimerEx ( "OnPlayerUnfreeze", time, false, "i", playerid ) );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Remover uma arma específica de um jogador.

	Params:
		- playerid: ID do jogador.
		- weaponid: ID da arma que será removida.

	Retorna:
		- 0 caso o id do jogador inválido ou arma inválida.
		- 1 caso for executada com sucesso.
\*----------------------------------------------------------------------------*/
stock RemovePlayerWeapon ( playerid, weaponid )
{
	if ( playerid == INVALID_PLAYER_ID ||	!IsPlayerConnected ( playerid ) ||	weaponid < 0 || weaponid > 46 )
		return 0;

	new
		int_old_weapon [ 13 ],
		int_old_ammo [ 13 ];

	for ( new slot = 0; slot < 13; slot++ )
		GetPlayerWeaponData ( playerid, slot, int_old_weapon [ slot ], int_old_ammo [ slot ] );

	ResetPlayerWeapons ( playerid );

	for ( new slot = 0; slot < 13; slot++ )
	{
		if ( int_old_weapon [ slot ] == weaponid || int_old_ammo [ slot ] == 0 )
			continue;

		GivePlayerWeapon ( playerid, int_old_weapon [ slot ], int_old_ammo [ slot ] );
	}

	GivePlayerWeapon ( playerid, 0, 1 );

	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a saúde do veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- A saúde do veículo (float).
\*----------------------------------------------------------------------------*/
stock Float: GetVehicleHealthEx ( vehicleid )
{
	new
		Float: flo_vehicle_health;

	GetVehicleHealth ( vehicleid, flo_vehicle_health );

	return flo_vehicle_health;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Remover qualquer arma de um slot específico de um jogador.

	Params:
		- playerid: ID do jogador.
		- slotid: ID do slot que a arma será removida.

	Retorna:
		- 0 caso o id do jogador inválido ou slot inválido.
		- 1 caso for executada com sucesso.
\*----------------------------------------------------------------------------*/
stock RemovePlayerSlotWeapon ( playerid, slotid )
{
	if ( playerid == INVALID_PLAYER_ID || !IsPlayerConnected ( playerid ) || slotid < 0 || slotid > 12 )
		return 0;

	new
		int_old_weapon [ 13 ],
		int_old_ammo [ 13 ];

	for ( new slot = 0; slot < 13; slot++ )
		GetPlayerWeaponData ( playerid, slot, int_old_weapon [ slot ], int_old_ammo [ slot ] );

	ResetPlayerWeapons ( playerid );

	for ( new slot = 0; slot < 13; slot++ )
		if ( slot == slotid )
			continue;

		GivePlayerWeapon ( playerid, int_old_weapon [ slot ], int_old_ammo [ slot ] );

	GivePlayerWeapon ( playerid, 0, 1 );

	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um veículo está ocupado com algum jogador.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- 0 caso o veículo estiver desocupado.
		- 1 caso o veículo estiver ocupado.
\*----------------------------------------------------------------------------*/
stock IsVehicleOccupied ( vehicleid )
{
	for ( new slots = GetMaxPlayers ( ), i; i < slots; i++  )
	{
		if ( !IsPlayerConnected ( i ) )
			continue;

		if ( IsPlayerInVehicle ( i, vehicleid ) )
			return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Teleportar um jogador para um veículo.

	Params:
		- playerid: ID do jogador.
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock TeleportPlayerToVehicle ( playerid, vehicleid )
{
	new
		Float: flo_pos [ 3 ];

	GetVehiclePos ( vehicleid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
	SetPlayerPos ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Teleportar um jogador para outro jogador.

	Params:
		- playerid: ID do jogador 1.
		- targetid: ID do jogador 2.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock TeleportPlayerToPlayer ( playerid, targetid )
{
	new
		Float:flo_pos [ 3 ];

	GetPlayerPos ( targetid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );
	SetPlayerPos ( playerid, flo_pos [ 0 ], flo_pos [ 1 ], flo_pos [ 2 ] );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um jogador é motorista de algum veículo.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- 0 caso o jogador não for um motorista.
		- 1 caso o jogador for um motorista.
\*----------------------------------------------------------------------------*/
stock IsPlayerDriver ( playerid )
{
    if ( GetPlayerState ( playerid ) == PLAYER_STATE_DRIVER )
    	return true;

    return false;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um jogador é um passageiro de algum veículo.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- 0 caso o jogador não for um passageiro.
		- 1 caso o jogador for um passageiro.
\*----------------------------------------------------------------------------*/
stock IsPlayerPassenger ( playerid )
{
    if ( GetPlayerState ( playerid ) == PLAYER_STATE_PASSENGER )
    	return true;

    return false;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um jogador está nadando.

	Params:
		- playerid: ID do jogador.

	Retorna:
		- 0 caso o jogador não estiver nadando.
		- 1 caso o jogador estiver nadando.
\*----------------------------------------------------------------------------*/
stock IsPlayerSwimming ( playerid )
{
	if ( IsPlayerInAnyVehicle ( playerid ) || GetPlayerState ( playerid ) != PLAYER_STATE_ONFOOT )
		return 0;

	new
		str_anim_lib [ 32 ],
		str_anim_name [ 32 ];

	GetAnimationName ( GetPlayerAnimationIndex ( playerid ), str_anim_lib, 32, str_anim_name,32 );

	if ( !strcmp ( str_anim_lib, "SWIM", true ) &&
		(!strcmp ( str_anim_name, "SWIM_CRAWL", true ) ||
		!strcmp ( str_anim_name, "SWIM_GLIDE", true ) ||
		!strcmp ( str_anim_name, "SWIM_UNDER", true ) ||
		!strcmp ( str_anim_name, "SWIM_TREAD", true ) ||
		!strcmp ( str_anim_name, "SWIM_BREAST", true ) ||
		!strcmp ( str_anim_name, "SWIM_DIVE_UNDER", true ) ||
		!strcmp ( str_anim_name, "SWIM_DIVE_GLIDE", true ) ) )
		return 1;

	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Desvirar um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock FlipVehicle ( vehicleid )
{
	SetVehicleZAngle ( vehicleid, GetVehicleZAnglef ( vehicleid ) );
	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o nome do veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- 'invalído' caso o id do veículo seja inválido.
		- O nome do veículo (string) caso for válido.
\*----------------------------------------------------------------------------*/
stock GetVehicleName ( vehicleid )
{
	new
		str_vehicle_name [ 22 ];

	switch ( GetVehicleModel ( vehicleid ) )
	{
		case 400: str_vehicle_name = "Landstalker";
		case 401: str_vehicle_name = "Bravura";
		case 402: str_vehicle_name = "Buffalo";
		case 403: str_vehicle_name = "Linerunner";
		case 404: str_vehicle_name = "Perenniel";
		case 405: str_vehicle_name = "Sentinel";
		case 406: str_vehicle_name = "Dumper";
		case 407: str_vehicle_name = "Firetruck";
		case 408: str_vehicle_name = "Trashmaster";
		case 409: str_vehicle_name = "Stretch";
		case 410: str_vehicle_name = "Manana";
		case 411: str_vehicle_name = "Infernus";
		case 412: str_vehicle_name = "Voodoo";
		case 413: str_vehicle_name = "Pony";
		case 414: str_vehicle_name = "Mule";
		case 415: str_vehicle_name = "Cheetah";
		case 416: str_vehicle_name = "Ambulance";
		case 417: str_vehicle_name = "Leviathan";
		case 418: str_vehicle_name = "Moonbeam";
		case 419: str_vehicle_name = "Esperanto";
		case 420: str_vehicle_name = "Taxi";
		case 421: str_vehicle_name = "Washigton";
		case 422: str_vehicle_name = "Bobcat";
		case 423: str_vehicle_name = "Mr Whoopee";
		case 424: str_vehicle_name = "BF Injection";
		case 425: str_vehicle_name = "Hunter";
		case 426: str_vehicle_name = "Premier";
		case 427: str_vehicle_name = "Enforcer";
		case 428: str_vehicle_name = "Securicar";
		case 429: str_vehicle_name = "Banshee";
		case 430: str_vehicle_name = "Predator";
		case 431: str_vehicle_name = "Bus";
		case 432: str_vehicle_name = "Rhino";
		case 433: str_vehicle_name = "Barracks";
		case 434: str_vehicle_name = "Hotknife";
		case 435: str_vehicle_name = "Article Trailer";
		case 436: str_vehicle_name = "Previon";
		case 437: str_vehicle_name = "Coach";
		case 438: str_vehicle_name = "Cabbie";
		case 439: str_vehicle_name = "Stallion";
		case 440: str_vehicle_name = "Rumpo";
		case 441: str_vehicle_name = "RC Bandit";
		case 442: str_vehicle_name = "Romero";
		case 443: str_vehicle_name = "Packer";
		case 444: str_vehicle_name = "Monster";
		case 445: str_vehicle_name = "Admiral";
		case 446: str_vehicle_name = "Squallo";
		case 447: str_vehicle_name = "Seasparrow";
		case 448: str_vehicle_name = "Pizzaboy";
		case 449: str_vehicle_name = "Tram";
		case 450: str_vehicle_name = "Article Trailer 2";
		case 451: str_vehicle_name = "Turismo";
		case 452: str_vehicle_name = "Speeder";
		case 453: str_vehicle_name = "Reefer";
		case 454: str_vehicle_name = "Tropic";
		case 455: str_vehicle_name = "Flatbed";
		case 456: str_vehicle_name = "Yankee";
		case 457: str_vehicle_name = "Caddy";
		case 458: str_vehicle_name = "Solair";
		case 459: str_vehicle_name = "Topfun Van";
		case 460: str_vehicle_name = "Skimmer";
		case 461: str_vehicle_name = "PCJ-600";
		case 462: str_vehicle_name = "Faggio";
		case 463: str_vehicle_name = "Freeway";
		case 464: str_vehicle_name = "RC Baron";
		case 465: str_vehicle_name = "RC Raider";
		case 466: str_vehicle_name = "Glendale";
		case 467: str_vehicle_name = "Oceanic";
		case 468: str_vehicle_name = "Sanchez";
		case 469: str_vehicle_name = "Sparrow";
		case 470: str_vehicle_name = "Patriot";
		case 471: str_vehicle_name = "Quad";
		case 472: str_vehicle_name = "Coastguard";
		case 473: str_vehicle_name = "Dinghy";
		case 474: str_vehicle_name = "Hermes";
		case 475: str_vehicle_name = "Sabre";
		case 476: str_vehicle_name = "Rustler";
		case 477: str_vehicle_name = "ZR-350";
		case 478: str_vehicle_name = "Walton";
		case 479: str_vehicle_name = "Regina";
		case 480: str_vehicle_name = "Comet";
		case 481: str_vehicle_name = "BMX";
		case 482: str_vehicle_name = "Burrito";
		case 483: str_vehicle_name = "Camper";
		case 484: str_vehicle_name = "Marquis";
		case 485: str_vehicle_name = "Baggage";
		case 486: str_vehicle_name = "Dozer";
		case 487: str_vehicle_name = "Maverick";
		case 488: str_vehicle_name = "San News Maverick";
		case 489: str_vehicle_name = "Rancher";
		case 490: str_vehicle_name = "FBI Rancher";
		case 491: str_vehicle_name = "Virgo";
		case 492: str_vehicle_name = "Greenwood";
		case 493: str_vehicle_name = "Jetmax";
		case 494: str_vehicle_name = "Hotring Racer";
		case 495: str_vehicle_name = "Sandking";
		case 496: str_vehicle_name = "Blista Compact";
		case 497: str_vehicle_name = "Police Maverick";
		case 498: str_vehicle_name = "Boxville";
		case 499: str_vehicle_name = "Benson";
		case 500: str_vehicle_name = "Mesa";
		case 501: str_vehicle_name = "RC Goblin";
		case 502: str_vehicle_name = "Hotring Racer";
		case 503: str_vehicle_name = "Hotring Racer";
		case 504: str_vehicle_name = "Bloodring Banger";
		case 505: str_vehicle_name = "Rancher";
		case 506: str_vehicle_name = "Super GT";
		case 507: str_vehicle_name = "Elegant";
		case 508: str_vehicle_name = "Journey";
		case 509: str_vehicle_name = "Bike";
		case 510: str_vehicle_name = "Mountain Bike";
		case 511: str_vehicle_name = "Beagle";
		case 512: str_vehicle_name = "Cropduster";
		case 513: str_vehicle_name = "Stuntplane";
		case 514: str_vehicle_name = "Tanker";
		case 515: str_vehicle_name = "Roadtrain";
		case 516: str_vehicle_name = "Nebula";
		case 517: str_vehicle_name = "Majestic";
		case 518: str_vehicle_name = "Buccaneer";
		case 519: str_vehicle_name = "Shamal";
		case 520: str_vehicle_name = "Hydra";
		case 521: str_vehicle_name = "FCR-900";
		case 522: str_vehicle_name = "NRG-500";
		case 523: str_vehicle_name = "HPV-1000";
		case 524: str_vehicle_name = "Cement Truck";
		case 525: str_vehicle_name = "TowTruck";
		case 526: str_vehicle_name = "Fortune";
		case 527: str_vehicle_name = "Cadrona";
		case 528: str_vehicle_name = "FBI Truck";
		case 529: str_vehicle_name = "Willard";
		case 530: str_vehicle_name = "Forklift";
		case 531: str_vehicle_name = "Tractor";
		case 532: str_vehicle_name = "Combine Harvester";
		case 533: str_vehicle_name = "Feltzer";
		case 534: str_vehicle_name = "Remington";
		case 535: str_vehicle_name = "Slamvan";
		case 536: str_vehicle_name = "Blade";
		case 537: str_vehicle_name = "Freight (Train)";
		case 538: str_vehicle_name = "Brownstreak (Train)";
		case 539: str_vehicle_name = "Vortex";
		case 540: str_vehicle_name = "Vincent";
		case 541: str_vehicle_name = "Bullet";
		case 542: str_vehicle_name = "Clover";
		case 543: str_vehicle_name = "Sadler";
		case 544: str_vehicle_name = "Firetruck LA";
		case 545: str_vehicle_name = "Hustler";
		case 546: str_vehicle_name = "Intruder";
		case 547: str_vehicle_name = "Primo";
		case 548: str_vehicle_name = "Cargobob";
		case 549: str_vehicle_name = "Tampa";
		case 550: str_vehicle_name = "Sunrise";
		case 551: str_vehicle_name = "Merit";
		case 552: str_vehicle_name = "Utility Van";
		case 553: str_vehicle_name = "Nevada";
		case 554: str_vehicle_name = "Yosemite";
		case 555: str_vehicle_name = "Windsor";
		case 556: str_vehicle_name = "Monster ''A''";
		case 557: str_vehicle_name = "Monster ''B''";
		case 558: str_vehicle_name = "Uranus";
		case 559: str_vehicle_name = "Jester";
		case 560: str_vehicle_name = "Sultan";
		case 561: str_vehicle_name = "Stratum";
		case 562: str_vehicle_name = "Elegy";
		case 563: str_vehicle_name = "Raindance";
		case 564: str_vehicle_name = "RC Tiger";
		case 565: str_vehicle_name = "Flash";
		case 566: str_vehicle_name = "Tahoma";
		case 567: str_vehicle_name = "Savanna";
		case 568: str_vehicle_name = "Bandito";
		case 569: str_vehicle_name = "Freight Flat Trailer";
		case 570: str_vehicle_name = "Streak Trailer";
		case 571: str_vehicle_name = "Kart";
		case 572: str_vehicle_name = "Mower";
		case 573: str_vehicle_name = "Dune";
		case 574: str_vehicle_name = "Sweeper";
		case 575: str_vehicle_name = "Broadway";
		case 576: str_vehicle_name = "Tornado";
		case 577: str_vehicle_name = "AT400";
		case 578: str_vehicle_name = "DFT-30";
		case 579: str_vehicle_name = "Huntley";
		case 580: str_vehicle_name = "Stafford";
		case 581: str_vehicle_name = "BF-400";
		case 582: str_vehicle_name = "Newsvan";
		case 583: str_vehicle_name = "Tug";
		case 584: str_vehicle_name = "Petrol Trailer";
		case 585: str_vehicle_name = "Emperor";
		case 586: str_vehicle_name = "Wayfarer";
		case 587: str_vehicle_name = "Euros";
		case 588: str_vehicle_name = "Hotdog";
		case 589: str_vehicle_name = "Club";
		case 590: str_vehicle_name = "Freight Box Trailer";
		case 591: str_vehicle_name = "Article Trailer 3";
		case 592: str_vehicle_name = "Andromada";
		case 593: str_vehicle_name = "Dodo";
		case 594: str_vehicle_name = "RC Cam";
		case 595: str_vehicle_name = "Launch";
		case 596: str_vehicle_name = "Police Car (LSPD)";
		case 597: str_vehicle_name = "Police Car (SFPD)";
		case 598: str_vehicle_name = "Police Car (LVPD)";
		case 599: str_vehicle_name = "Police Ranger";
		case 600: str_vehicle_name = "Picador";
		case 601: str_vehicle_name = "S.W.A.T";
		case 602: str_vehicle_name = "Alpha";
		case 603: str_vehicle_name = "Phoenix";
		case 604: str_vehicle_name = "Glendale Shit";
		case 605: str_vehicle_name = "Sadler Shit";
		case 606: str_vehicle_name = "Baggage Trailer ''A''";
		case 607: str_vehicle_name = "Baggage Trailer ''B''";
		case 608: str_vehicle_name = "Tug Stairs Trailer";
		case 609: str_vehicle_name = "Boxville";
		case 610: str_vehicle_name = "Farm Trailer";
		case 611: str_vehicle_name = "Utility Trailer";
		default: str_vehicle_name = "inválido";
	}
	return str_vehicle_name;
}


/*----------------------------------------------------------------------------*\
	Função:
		- Obter o status do motor do veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- 1 caso o motor do veículo estiver ligado.
		- 0 caso o motor do veículo estiver desligado.
\*----------------------------------------------------------------------------*/
stock GetVehicleEngineStatus ( vehicleid )
{
	new
		int_engine,
		int_lights,
		int_alarm,
		int_doors,
		int_bonnet,
		int_boot,
		int_objective;

    GetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, int_doors, int_bonnet, int_boot, int_objective );

	if ( int_engine == VEHICLE_PARAMS_ON )
		return 1;

	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verificar se um veículo está trancado.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- 1 caso o veículo estiver trancado.
		- 0 caso o veículo estiver destrancado.
\*----------------------------------------------------------------------------*/
stock IsVehicleLocked ( vehicleid )
{
	new
		int_engine,
		int_lights,
		int_alarm,
		int_doors,
		int_bonnet,
		int_boot,
		int_objective;

    GetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, int_doors, int_bonnet, int_boot, int_objective );
 
	if ( v_DOORS == true )
		return 1;

	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Trancar um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock LockVehicle ( vehicleid )
{
	new
		int_engine,
		int_lights,
		int_alarm,
		int_doors,
		int_bonnet,
		int_boot,
		int_objective;

    GetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, int_doors, int_bonnet, int_boot, int_objective );
	SetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, true, int_bonnet, int_boot, int_objective );

	return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Destrancar um veículo.

	Params:
		- vehicleid: ID do veículo.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock UnlockVehicle ( vehicleid )
{
	new
		int_engine,
		int_lights,
		int_alarm,
		int_doors,
		int_bonnet,
		int_boot,
		int_objective;

    GetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, int_doors, int_bonnet, int_boot, int_objective );
	SetVehicleParamsEx ( vehicleid, int_engine, int_lights, int_alarm, false, int_bonnet, int_boot, int_objective );

	return 0;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Enviar uma mensagem aos administradores RCON.

	Params:
		- color: Cor (hex) da mensagem.
		- message: Mensagem (string) a ser enviada.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SendAdminMessage ( color, const message [ ] )
{	
    for ( new slots = GetMaxPlayers( ), i; i < slots; i++ )
    {
    	if ( !IsPlayerConnected ( i ) )
			continue;

		if ( IsPlayerAdmin ( i ) )
			SendClientMessage ( i, color, message );
	}
    return;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Descongelar um jogardor

	Params:
		- playerid - jogador congelado

	Retorna:
		- 1
\*----------------------------------------------------------------------------*/
public OnPlayerUnfreeze ( playerid )
{
	TogglePlayerControllable ( playerid, true );
	DeletePVar ( playerid, "FreezeTimer" );
	
	return 1;
}

#undef isnull