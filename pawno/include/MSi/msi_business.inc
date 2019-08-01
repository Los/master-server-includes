/******************************************************************************
 *				MASTER SERVER INCLUDES - Business  							  *
 *	@Descrição:																  *
 *		Adiciona funções para criação e manipulação de empresas no jogo,	  *
 *		permitindo a um jogador comprar, vender e personalizar   			  *
 *		sua empresa, adicionando fundos e etc... 	                          *
 *	@Legal:																	  *
 *		Este código-fonte está sob os termos de licença da Mozilla Public	  *
 *		License, v. 2.0. Se uma cópia do MPL não for distribuida com este 	  *
 *		arquivo, você pode obter uma em http://mozilla.org/MPL/2.0/			  *
 *																			  *
 *		Os iniciais desenvolvedores deste código é Larceny e Lós.	  	      *
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

#if defined _MSi_business_included
	#endinput
#endif
#define _MSi_business_included

/*
native GetBusinessEntrancePos(businessid, &Float:x, &Float:y, &Float:z, &Float:a);
native GetBusinessExitPos(businessid, &Float:x, &Float:y, &Float:z, &Float:a);
native SetBusinessEntrancePos(businessid, Float:x, Float:y, Float:z, Float:a);
native SetBusinessExitPos(businessid, Float:x, Float:y, Float:z, Float:a);
native SetBusinessEntranceInterior(businessid, interior);
native SetBusinessExitInterior(businessid, interior);
native GetBusinessEntranceInterior(businessid);
native SetBusinessProducts(businessid, prods);
native SetBusinessOwner(businessid, owner[]);
native SetBusinessLocked(businessid, locked);
native SetBusinessName(businessid, bname[]);
native SetBusinessPrice(businessid, price);
native GetBusinessExitInterior(businessid);
native SetBusinessOwned(businessid, owned);
native SetBusinessCash(businessid, value);
native GetBusinessPickupID(businessid);
native GetBusinessProducts(businessid);
native GetBusinessPrice(businessid);
native IsBusinessLocked(businessid);
native GetBusinessOwner(businessid);
native IsBusinessOwned(businessid);
native GetBusinessCash(businessid);
native GetBusinessName(businessid);
native CreateBusiness(Float:Enterx, Float:Entery, Float:Enterz, Float:Entera,
 Float:Exitx, Float:Exity, Float:Exitz, Float:Exita,
 enterinterior = 0, exitinterior = 0, locked = 0,
 price = 0, cash = 0, owned = 0, owner[] = "Ninguem", name[] = "Indefinido");
*/

#if !defined MAX_BUSINESS
	#define MAX_BUSINESS 50
#endif

#if !defined MAX_BUSINESS_NAME
	#define MAX_BUSINESS_NAME 64
#endif

#define INVALID_BUSINESS_ID	-1

enum E_BUSINESS_DATA
{
	Float:E_BUSINESS_ENTERX,
	Float:E_BUSINESS_ENTERY,
	Float:E_BUSINESS_ENTERZ,
	Float:E_BUSINESS_ENTERA,
	Float:E_BUSINESS_EXITX,
	Float:E_BUSINESS_EXITY,
	Float:E_BUSINESS_EXITZ,
	Float:E_BUSINESS_EXITA,
	E_BUSINESS_ENTERINT,
	E_BUSINESS_EXITINT,
	E_BUSINESS_PRODCTS,
	E_BUSINESS_PICKUP,
	E_BUSINESS_LOCKED,
	E_BUSINESS_PRICE,
	E_BUSINESS_MONEY,
	E_BUSINESS_OWNED,
	E_BUSINESS_OWNER[MAX_PLAYER_NAME],
	E_BUSINESS_NAME[MAX_BUSINESS_NAME]
}
new g_eBusinessData[MAX_BUSINESS][E_BUSINESS_DATA];

/*----------------------------------------------------------------------------*\
	Função:
		- Cria uma empresa.

	Params:
		- Enterx: Coordenada X da entrada da empresa.
		- Entery: Coordenada Y da entrada da empresa.
		- Enterz: Coordenada Z da entrada da empresa.
		- Entera: Ângulo da entrada da empresa.

		- Exitx: Coordenada X da saída da empresa.
		- Exity: Coordenada Y da saída da empresa.
		- Exitz: Coordenada Z da saída da empresa.
		- Exita: Ângulo da saída da empresa.

		- enterinterior: 	ID do interior da entrada da empresa.
		- exitinterior: 	ID do interior da entrada da empresa.
		- locked: 			Empresa trancada ou destrancada.
		- price: 			Preço da empresa.

		- cash:				Quantia no cofre da empresa.
		- owned:			Empresa comprada.
		- owner[]:			Nome do dono da empresa.
		- name[]:			Nome da empresa.

	Retorna:
		- O ID da empresa criada.
\*----------------------------------------------------------------------------*/
stock CreateBusiness(Float:Enterx, Float:Entery, Float:Enterz, Float:Entera,
					 Float:Exitx, Float:Exity, Float:Exitz, Float:Exita,
					 enterinterior = 0, exitinterior = 0, locked = 0,
					 price = 0, cash = 0, owned = 0, owner[] = "Ninguem",
					 name[] = "Indefinido")
{
	new nBusinessCounter = GetFreeBusinessID();
	if(nBusinessCounter == INVALID_BUSINESS_ID)
	{
		print("ERROR: Limite maximo de empresas atingido! (MSi/MSi_business)");
		return 0;
	}

	g_eBusinessData[nBusinessCounter][E_BUSINESS_ENTERX] = Enterx;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_ENTERY] = Entery;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_ENTERZ] = Enterz;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_ENTERA] = Entera;

	g_eBusinessData[nBusinessCounter][E_BUSINESS_EXITX] = Exitx;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_EXITY] = Exity;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_EXITZ] = Exitz;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_EXITA] = Exita;

	g_eBusinessData[nBusinessCounter][E_BUSINESS_ENTERINT] = enterinterior;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_EXITINT] = exitinterior;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_LOCKED] = locked;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_PRICE] = price;

	g_eBusinessData[nBusinessCounter][E_BUSINESS_MONEY] = cash;
	g_eBusinessData[nBusinessCounter][E_BUSINESS_OWNED] = owned;

	format(g_eBusinessData[nBusinessCounter][E_BUSINESS_OWNER], MAX_PLAYER_NAME, "%s", owner);
	format(g_eBusinessData[nBusinessCounter][E_BUSINESS_NAME], MAX_BUSINESS_NAME, "%s", name);

	if(g_eBusinessData[nBusinessCounter][E_BUSINESS_OWNED] == 0) g_eBusinessData[nBusinessCounter][E_BUSINESS_PICKUP] = CreatePickup(1272, 1, Enterx, Entery, Enterz);
	else g_eBusinessData[nBusinessCounter][E_BUSINESS_PICKUP] = CreatePickup(1239, 1, Enterx, Entery, Enterz);

	return nBusinessCounter;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir a posição da entrada de uma empresa.

	Params:
		- businessid: ID da empresa que terá a posição alterada.
		- x: Coordenada X da entrada da empresa.
		- y: Coordenada Y da entrada da empresa.
		- z: Coordenada Z da entrada da empresa.
		- a: Angulô da entrada da empresa.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetBusinessEntrancePos(businessid, Float:x, Float:y, Float:z, Float:a)
{
	g_eBusinessData[businessid][E_BUSINESS_ENTERX] = x;
	g_eBusinessData[businessid][E_BUSINESS_ENTERY] = y;
	g_eBusinessData[businessid][E_BUSINESS_ENTERZ] = z;
	g_eBusinessData[businessid][E_BUSINESS_ENTERA] = a;
	DestroyPickup(g_eBusinessData[businessid][E_BUSINESS_PICKUP]);
	if(g_eBusinessData[businessid][E_BUSINESS_OWNED] == 0) g_eBusinessData[businessid][E_BUSINESS_PICKUP] = CreatePickup(1272, 1, x, y, z);
	else g_eBusinessData[businessid][E_BUSINESS_PICKUP] = CreatePickup(1239, 1, x, y, z);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a posição da entrada de uma empresa.

	Params:
		- businessid: ID da empresa que terá a posição obtida.
		- x: Coordenada X da entrada da empresa, passa por referência.
		- y: Coordenada Y da entrada da empresa, passa por referência.
		- z: Coordenada Z da entrada da empresa, passa por referência.
		- a: Angulô da entrada da empresa, passa por referência.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock GetBusinessEntrancePos(businessid, &Float:x, &Float:y, &Float:z, &Float:a)
{
	x = g_eBusinessData[businessid][E_BUSINESS_ENTERX];
	y = g_eBusinessData[businessid][E_BUSINESS_ENTERY];
	z = g_eBusinessData[businessid][E_BUSINESS_ENTERZ];
	a = g_eBusinessData[businessid][E_BUSINESS_ENTERA];
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir a posição da saída de uma empresa.

	Params:
		- businessid: ID da empresa que terá a posição alterada.
		- x: Coordenada X da saída da empresa.
		- y: Coordenada Y da saída da empresa.
		- z: Coordenada Z da saída da empresa.
		- a: Angulô da saída da empresa.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetBusinessExitPos(businessid, Float:x, Float:y, Float:z, Float:a)
{
	g_eBusinessData[businessid][E_BUSINESS_EXITX] = x;
	g_eBusinessData[businessid][E_BUSINESS_EXITY] = y;
	g_eBusinessData[businessid][E_BUSINESS_EXITZ] = z;
	g_eBusinessData[businessid][E_BUSINESS_EXITA] = a;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter a posição da saída de uma empresa.

	Params:
		- businessid: ID da empresa que terá a posição obtida.
		- x: Coordenada X da saída da empresa, passa por referência.
		- y: Coordenada Y da saída da empresa, passa por referência.
		- z: Coordenada Z da saída da empresa, passa por referência.
		- a: Angulô da saída da empresa, passa por referência.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock GetBusinessExitPos(businessid, &Float:x, &Float:y, &Float:z, &Float:a)
{
	x = g_eBusinessData[businessid][E_BUSINESS_EXITX];
	y = g_eBusinessData[businessid][E_BUSINESS_EXITY];
	z = g_eBusinessData[businessid][E_BUSINESS_EXITZ];
	a = g_eBusinessData[businessid][E_BUSINESS_EXITA];
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir o ID do interior da entrada de uma empresa.

	Params:
		- businessid: ID da empresa que terá o interior alterado.
		- interior: ID do interior.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetBusinessEntranceInterior(businessid, interior)
{
	g_eBusinessData[businessid][E_BUSINESS_ENTERINT] = interior;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtem o ID do interior da entrada de uma empresa.

	Params:
		- businessid: ID da empresa que terá o interior obtido.

	Retorna:
		- O ID do interior da entrada da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessEntranceInterior(businessid, interior)
{
	return g_eBusinessData[businessid][E_BUSINESS_ENTERINT];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Definir o ID do interior da saída de uma empresa.

	Params:
		- businessid: ID da empresa que terá o interior alterado.
		- interior: ID do interior.

	Retorna:
		- Esta função não retorna um valor específico.
\*----------------------------------------------------------------------------*/
stock SetBusinessExitInterior(businessid, interior)
{
	g_eBusinessData[businessid][E_BUSINESS_EXITINT] = interior;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtem o ID do interior da saída de uma empresa.

	Params:
		- businessid: ID da empresa que terá o interior obtido.

	Retorna:
		- O ID do interior da saída da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessExitInterior(businessid)
{
	return g_eBusinessData[businessid][E_BUSINESS_EXITINT];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Tranca/Destranca uma empresa.

	Params:
		- businessid: ID da empresa que será trancada/destrancada.
		- locked: Tranca/Destranca empresa.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessLocked(businessid, locked)
{
	if(locked) g_eBusinessData[businessid][E_BUSINESS_LOCKED] = 1;
	else g_eBusinessData[businessid][E_BUSINESS_LOCKED] = 0;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verifica se uma empresa está trancada.

	Params:
		- businessid: ID da empresa que será verificada se está trancada.

	Retorna:
		- Retorna se a empresa está trancada ou não.
\*----------------------------------------------------------------------------*/
stock IsBusinessLocked(businessid)
{
	return (g_eBusinessData[businessid][E_BUSINESS_LOCKED]);
}

/*----------------------------------------------------------------------------*\
	Função:
		- Altera o preço de uma empresa.

	Params:
		- businessid: ID da empresa que será alterado o preço.
		- price: Preço da empresa.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessPrice(businessid, price)
{
	g_eBusinessData[businessid][E_BUSINESS_PRICE] = price;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém o preço de uma empresa.

	Params:
		- businessid: ID da empresa que terá o preço obtido.

	Retorna:
		- O preço da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessPrice(businessid)
{
	return g_eBusinessData[businessid][E_BUSINESS_PRICE];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Altera o dinheiro do cofre de uma empresa.

	Params:
		- businessid: ID da empresa que será alterado o dinheiro do cofre.
		- value: Dinheiro do cofre da empresa.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessCash(businessid, value)
{
	g_eBusinessData[businessid][E_BUSINESS_MONEY] = value;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém o dinheiro do cofre de uma empresa.

	Params:
		- businessid: ID da empresa que terá o dinheiro obtido.

	Retorna:
		- O dinheiro do cofre da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessCash(businessid)
{
	return g_eBusinessData[businessid][E_BUSINESS_MONEY];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Define a empresa como comprada.

	Params:
		- businessid: ID da empresa que será definida como comprada ou não.
		- owned: Define como comprada.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessOwned(businessid, owned)
{
	if(owned) g_eBusinessData[businessid][E_BUSINESS_OWNED] = 1;
	else g_eBusinessData[businessid][E_BUSINESS_OWNED] = 0;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Verifica se uma empresa está comprada.

	Params:
		- businessid: ID da empresa que será verificada se está comprada.

	Retorna:
		- Se a empresa está comprada ou não.
\*----------------------------------------------------------------------------*/
stock IsBusinessOwned(businessid)
{
	return (g_eBusinessData[businessid][E_BUSINESS_OWNED]);
}

/*----------------------------------------------------------------------------*\
	Função:
		- Define o nome do dono de uma empresa.

	Params:
		- businessid: ID da empresa que será alterado o nome do dono.
		- owner[]: Nome do dono da empresa.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessOwner(businessid, owner[])
{
	format(g_eBusinessData[businessid][E_BUSINESS_OWNER], MAX_PLAYER_NAME, "%s", owner);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém o nome do dono de uma empresa.

	Params:
		- businessid: ID da empresa que será obtido o nome do dono.

	Retorna:
		- O nome do dono da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessOwner(businessid)
{
	new str_Buffer[MAX_BUSINESS_NAME];
	format(str_Buffer, MAX_BUSINESS_NAME, "%s", g_eBusinessData[businessid][E_BUSINESS_OWNER]);
	return str_Buffer;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Define o nome de uma empresa.

	Params:
		- businessid: ID da empresa que será definido o nome.
		- bname: Nome da emnpresa.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessName(businessid, bname[])
{
	format(g_eBusinessData[businessid][E_BUSINESS_NAME], MAX_BUSINESS_NAME, "%s", bname);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém o nome de uma empresa.

	Params:
		- businessid: ID da empresa que será obtido o nome.

	Retorna:
		- O nome da empresa.
\*----------------------------------------------------------------------------*/
stock GetBusinessName(businessid)
{
	new str_Buffer[MAX_BUSINESS_NAME];
	format(str_Buffer, MAX_BUSINESS_NAME, "%s", g_eBusinessData[businessid][E_BUSINESS_NAME]);
	return str_Buffer;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Define a quantia de produtos da empresa.

	Params:
		- businessid: ID da empresa que será definido os produtos.
		- prods: Quantia de produtos.

	Retorna:
		- Esta função não retorna nenhum valor.
\*----------------------------------------------------------------------------*/
stock SetBusinessProducts(businessid, prods)
{
	g_eBusinessData[businessid][E_BUSINESS_PRODCTS] = prods;
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém os produtos de uma empresa.

	Params:
		- businessid: ID da empresa que será obtido os produtos.

	Retorna:
		- Quantia de produtos de uma empresa..
\*----------------------------------------------------------------------------*/
stock GetBusinessProducts(businessid)
{
	return g_eBusinessData[businessid][E_BUSINESS_PRODCTS];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obtém o ID do icone de uma empresa.

	Params:
		- businessid: ID da empresa que será obtido o ID do icone.

	Retorna:
		- O ID do icone da empresa
\*----------------------------------------------------------------------------*/
stock GetBusinessPickupID(businessid)
{
	return g_eBusinessData[businessid][E_BUSINESS_PICKUP];
}

/*----------------------------------------------------------------------------*\
	Função:
		- Salva os dados de uma empresa.

	Params:
		- businessid: ID da empresa que será salva.

	Retorna:
		- Esta função não retorna um valor.
\*----------------------------------------------------------------------------*/
stock SaveBusinessData(businessid)
{
	new fileToWrite[48];
	format(fileToWrite, sizeof(fileToWrite), "MSi/business/business_%i.ini", businessid);
	new File: hFile = fopen(fileToWrite, io_write);
	if (hFile)
	{
		new valueToWrite[128];
		format(valueToWrite, 128, "EnterX = %f\n", g_eBusinessData[businessid][E_BUSINESS_ENTERX]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "EnterY = %f\n", g_eBusinessData[businessid][E_BUSINESS_ENTERY]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "EnterZ = %f\n", g_eBusinessData[businessid][E_BUSINESS_ENTERZ]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "EnterA = %f\n", g_eBusinessData[businessid][E_BUSINESS_ENTERA]); 	fwrite(hFile, valueToWrite);

		format(valueToWrite, 128, "ExitX = %f\n", g_eBusinessData[businessid][E_BUSINESS_EXITX]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "ExitY = %f\n", g_eBusinessData[businessid][E_BUSINESS_EXITY]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "ExitZ = %f\n", g_eBusinessData[businessid][E_BUSINESS_EXITZ]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "ExitA = %f\n", g_eBusinessData[businessid][E_BUSINESS_EXITA]); 		fwrite(hFile, valueToWrite);

		format(valueToWrite, 128, "EnterInt = %i\n", g_eBusinessData[businessid][E_BUSINESS_ENTERINT]); fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "ExitInt = %i\n", g_eBusinessData[businessid][E_BUSINESS_EXITINT]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Products = %i\n", g_eBusinessData[businessid][E_BUSINESS_PRODCTS]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Locked = %i\n", g_eBusinessData[businessid][E_BUSINESS_LOCKED]); 	fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Price = %i\n", g_eBusinessData[businessid][E_BUSINESS_PRICE]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Money = %i\n", g_eBusinessData[businessid][E_BUSINESS_MONEY]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Owned = %i\n", g_eBusinessData[businessid][E_BUSINESS_OWNED]); 		fwrite(hFile, valueToWrite);

		format(valueToWrite, 128, "Owner = %s\n", g_eBusinessData[businessid][E_BUSINESS_OWNER]); 		fwrite(hFile, valueToWrite);
		format(valueToWrite, 128, "Name = %s\n", g_eBusinessData[businessid][E_BUSINESS_NAME]); 		fwrite(hFile, valueToWrite);
		fclose(hFile);
	}
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Carrega os dados de uma empresa.

	Params:
		- businessid: ID da empresa que será caregada.

	Retorna:
		- Esta função não retorna um valor.

	Notas:
		- Caso a empresa carregada existir, ela será criada.
\*----------------------------------------------------------------------------*/
stock LoadBusinessData(businessid)
{
	new fileToRead[48];
	format(fileToRead, sizeof(fileToRead), "MSi/business/business_%i.ini", businessid);

	if(!fexist(fileToRead))
	{
		printf("ERROR: O arquivo %s não existe, por isso, não pode ser lido!", fileToRead);
		return 0;
	}

	new	str_Buffer[128],
		File:file = fopen(fileToRead, io_read);
    while(fread(file, str_Buffer))
    {
        if(strfind(str_Buffer, "EnterX", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("EnterX") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_ENTERX] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "EnterY", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("EnterY") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_ENTERY] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "EnterZ", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("EnterZ") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_ENTERZ] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "EnterA", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("EnterA") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_ENTERA] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "ExitX", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("ExitX") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_EXITX] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "ExitY", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("ExitY") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_EXITY] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "ExitZ", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("ExitZ") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_EXITZ] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "ExitA", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("ExitA") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_EXITA] = floatstr(str_Buffer);
        }
        else if(strfind(str_Buffer, "EnterInt", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("EnterInt") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_ENTERINT] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "ExitInt", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("ExitInt") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_EXITINT] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Products", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Products") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_PRODCTS] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Locked", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Locked") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_LOCKED] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Price", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Price") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_PRICE] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Money", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Money") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_MONEY] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Owned", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Owned") + 3);
        	g_eBusinessData[businessid][E_BUSINESS_OWNED] = strval(str_Buffer);
        }
        else if(strfind(str_Buffer, "Owner", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Owner") + 3);
        	format(g_eBusinessData[businessid][E_BUSINESS_OWNER], MAX_PLAYER_NAME, "%s", str_Buffer);
        }
        else if(strfind(str_Buffer, "Name", true) == 0)
        {
        	strdel(str_Buffer, 0, strlen("Name") + 3);
        	format(g_eBusinessData[businessid][E_BUSINESS_NAME], MAX_BUSINESS_NAME, "%s", str_Buffer);
        }
    }
    fclose(file);
    if (g_eBusinessData[businessid][E_BUSINESS_ENTERX] != 0.0 && g_eBusinessData[businessid][E_BUSINESS_ENTERY] != 0.0)
    	CreateBusiness(g_eBusinessData[businessid][E_BUSINESS_ENTERX],
    			   g_eBusinessData[businessid][E_BUSINESS_ENTERY],
    			   g_eBusinessData[businessid][E_BUSINESS_ENTERZ],
    			   g_eBusinessData[businessid][E_BUSINESS_ENTERA],
    			   g_eBusinessData[businessid][E_BUSINESS_EXITX],
    			   g_eBusinessData[businessid][E_BUSINESS_EXITY],
    			   g_eBusinessData[businessid][E_BUSINESS_EXITZ],
    			   g_eBusinessData[businessid][E_BUSINESS_EXITA],
    			   g_eBusinessData[businessid][E_BUSINESS_ENTERINT],
    			   g_eBusinessData[businessid][E_BUSINESS_EXITINT],
    			   g_eBusinessData[businessid][E_BUSINESS_LOCKED],
    			   g_eBusinessData[businessid][E_BUSINESS_PRICE],
    			   g_eBusinessData[businessid][E_BUSINESS_MONEY],
    			   g_eBusinessData[businessid][E_BUSINESS_OWNED],
    			   g_eBusinessData[businessid][E_BUSINESS_OWNER],
    			   g_eBusinessData[businessid][E_BUSINESS_NAME]);
	return 1;
}

/*----------------------------------------------------------------------------*\
	Função:
		- Obter o ID de uma empresa livre.

	Params:
		-

	Retorna:
		- O ID da emmpresa livre, caso tiver.
		- INVALID_BUSINESS_ID, caso não houver empresa livre.
\*----------------------------------------------------------------------------*/
stock GetFreeBusinessID()
{
	for (new iii = 0; iii < MAX_BUSINESS; iii++)
	{
		if (g_eBusinessData[iii][E_BUSINESS_ENTERX] == 0.0 && g_eBusinessData[iii][E_BUSINESS_ENTERY] == 0.0)
		{
			return iii;
		}
	}
	return INVALID_BUSINESS_ID;
}