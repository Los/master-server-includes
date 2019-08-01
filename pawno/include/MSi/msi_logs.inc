/******************************************************************************
 *				MASTER SERVER INCLUDES - Logs  								  *
 *	@Descrição:																  *
 *		Adiciona funções para criação e manipulação de logs sem qualquer	  *
 *		dificuldade									                          *
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

#if defined _msi_logs_included
	#endinput
#endif

#define _msi_logs_included
#define LogExists fexist

/*
native WriteLog(File[], string[]);
native DeleteLog(File[]);
native CreateLog(File[]);
native LogExists(File[]);
*/

/*----------------------------------------------------------------------------*\
Função:
	Escrever em um log.

Params:
	File - Arquivo a ser escrito
	str_write - O que vai ser escrito

Retorna:
	0 caso o arquivo não existir
	1 caso foi escrito com sucesso
\*----------------------------------------------------------------------------*/
stock WriteLog ( File[ ], str_write[ ] )
{
	if ( !LogExists ( File ) )
	{
		printf ( "ERROR: Arquivo de log não encontrado! (%s) (MSI/msi_logs)", File );
		return 0;
	}

	new
		str_formatted [ 300 ];

	if ( strlen ( str_write ) > 128 )
		#error String maior que 128 caracteres

    new
		year,
		month,
		day,
		hour,
		minute,
		second;

    getdate ( year, month, day );
    gettime ( hour, minute, second );

    format ( str_formatted, sizeof str_formatted, "(%02d/%02d/%d) [%02d:%02d] %s\r\n", day, month, year, hour, minute, second, str_write );

    new
    	File: log_file = fopen ( File, io_append );

    fwrite ( log_file, str_formatted );
    fclose ( log_file );

    return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Deletar um log.

Params:
	File - Arquivo a ser deletado

Retorna:
	0 caso o arquivo não existir
	1 caso for deletado com sucesso
\*----------------------------------------------------------------------------*/
stock DeleteLog ( File[ ] )
{
	if ( !LogExists ( File ) )
	{
		printf ( "ERROR: Arquivo de log não encontrado! (%s) (MSI/msi_logs)", File );
		return 0;
	}

	fremove ( File );

	return 1;
}

/*----------------------------------------------------------------------------*\
Função:
	Criar um log.

Params:
	File - Arquivo a ser criado

Retorna:
	0 caso o arquivo não existir
	1 caso for criado com sucesso
\*----------------------------------------------------------------------------*/
stock CreateLog ( File[ ] )
{
    if ( LogExists ( File ) )
    {
        printf ( "ERROR: Arquivo já existe! (%s) (MSI/msi_logs)", File );
        return 0;
    }

    new File: log_file = fopen ( File, io_write );
    fclose ( log_file );

    return 1;
}