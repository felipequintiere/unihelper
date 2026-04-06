#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #include <stdint.h>
// #include <inttypes.h>  // format specifiers

#include "./include/macros.h"
#include "./include/types.h"
#include "./include/flags.h"
#include "./include/util.h"
#include "./include/ler_entrada.h"
#include "./include/criar_registro.h"
#include "./include/editar_registro.h"
#include "./include/remover_registro.h"

#define ARQUIVO_DADOS "./dados.bin"
void buscar_registro_nome(const char * const arquivo);

int main(int argc, char *argv[])
{
	char *arquivo = ARQUIVO_DADOS;

	if (argc >= 2)
	{
		if (!strcmp("-h",argv[1]) || !strcmp("--help",argv[1]))
		{
			flag_help(argv[0]);  // argv[0]: nome do programa
			exit(EXIT_SUCCESS);
		}
		if (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version"))
		{
			flag_version(argv[0]);
			exit(EXIT_SUCCESS);
		}
		if (!strcmp(argv[1],"-f") || !strcmp(argv[1],"--file"))
		{
			if (argc == 2)
			{
				fprintf(stderr,
					"error: a value is required for '--file <FILE>' but none "
					"was supplied\n\nFor more information, try '--help'.\n"
				);
				exit(EXIT_FAILURE);
			}
			else if (argc > 3)
			{
				fprintf(stderr,
					"error: unrecognized subcommand '%s'"
					"\n\nFor more information, try '--help'.\n", argv[3]
				);
				exit(EXIT_FAILURE);
			}
			else
			{
				/*
				// para forçar o usuário a criar o arquivo
				FILE *fp;
				if ((fp = fopen(argv[2],"rb")) == NULL)
				{
					fprintf(stderr,"error: file '%s' does not exist\n",argv[2]);
					exit(EXIT_FAILURE);
				}
				fclose(fp);
				*/

				arquivo = argv[2]; // armazenar o nome do arquivo escolhido
				PRINT_DEBUG("%s\n",arquivo);
			}
		}
		else
		{
			flag_invalid(argv);  // passa todos os argumentos
			exit(EXIT_FAILURE);
		}
	}

#if defined(DEBUG) && DEBUG==1
	system("clear||cls");
#endif

	char entrada[ENTRADA_LEN+1] = {0};

	for (;;)
	{
		PRINT_STR(CYAN,"\n"
		"[1] criar registro\n"
		"[2] editar registro\n"
		"[3] remover registro\n"
		"[4] buscar registro por id\n"
		"[5] buscar registro por nome\n"
		"[6] listar registros\n"
		"[7] sair\n\n");
		PRINT_STR(PURPLE,"Escolha uma opção: ");

		ler_entrada(ENTRADA_LEN+1,entrada);	
		//         scanf(" %c", &option); 
		// nota:
		// Em uma entrada como "abcde...", esse scanf leria o
		// primeiro caractere, porém, os demais ficariam dentro
		// do input buffer. Consequentemente, as próximas
		// chamadas do scanf leriam esses valores armazenados no
		// buffer 

		switch (entrada[0])
		{
			// ./src/criar_registro.c
			case '1': criar_registro(id_unico_prox(arquivo),arquivo);
				break;
			case '2': editar_registro(arquivo); // ./src/editar_registro.c
				break;
			case '3': remover_registro(arquivo); // ./src/remover_registro.c
				break;
			case '4': 
					  system("clear||cls");
					  buscar_registro_id(arquivo); // ./src/util.c
				break;
			case '5': buscar_registro_nome(arquivo);
				break;
			case '6': listar_registros(arquivo); // ./src/util.c
				break;
			case '7': exit(EXIT_SUCCESS);

			default:
				fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
		}
	}
	return EXIT_SUCCESS;
}

void buscar_registro_nome(const char * const arquivo)
{
    char entrada[NOME_LEN+1];
    int ultimo_id;
	Membro *membro = (Membro*) malloc(sizeof(Membro));

    if ( (ultimo_id = id_unico_prox(arquivo)) == 0)
    {
        PRINT_STR(RED,"\nnão há dados armazenados em '%s'!\n",arquivo);
		return;
    }

	system("clear||cls");
	PRINT_STR(PURPLE,"BUSCAR REGISTRO POR NOME:\n");

    PRINT_STR(GREEN,"insira o texto: ");
	ler_entrada(NOME_LEN+1,entrada);
	int count = 0;
	for (int id=0; id<ultimo_id; id++)
	{
		arquivo_para_registro(membro,id,arquivo);
		if (strstr(membro->nome,entrada) != NULL && 
			membro->status_de_validacao != 0)
		{
			printf("\n----------------------------------------\n");
			mostrar_registro(membro);	
			count++;
		}
	}
	if (count)
	{
		printf("\n----------------------------------------\n");
	}
	else
	{
		PRINT_STR(RED,"\nnenhum resultado encontrado!\n");
	}
}
/*
// man 3 string
char *strstr(const char *haystack, const char *needle);
		Find the first occurrence of the  substring  needle  in
		the  string  haystack, returning a pointer to the found
		substring.

// man 3 strstr
RETURN VALUE
		These functions return a pointer to the beginning of  the  lo‐
		cated substring, or NULL if the substring is not found.

		If  needle  is  the  empty  string, the return value is always
		haystack itself.
*/

