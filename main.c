#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// consider using
// #include <stdint.h>
// #include <inttypes.h>  // for format specifiers
// note: enums can have different sizes

#include <stdbool.h>

#include "./include/macros.h"
#include "./include/types.h"
#include "./include/flags.h"
#include "./include/criar_registro.h"

#define TAM_REGISTRO 451L
#define ARQUIVO_DADOS "./dados.bin"

void ler_entrada(int, char entrada[*]);

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
				FILE *fp;
				if ((fp = fopen(argv[2],"rb")) == NULL)
				{
					fprintf(stderr,"error: file '%s' does not exist\n",argv[2]);
					exit(EXIT_FAILURE);
				}
				fclose(fp);

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
		" [1] criar registro\n"
		" [2] editar registro\n"
		" [3] remover registro\n"
		" [4] buscar registro por id\n"
		" [5] buscar registro por nome\n"
		" [6] listar registros\n"
		" [7] sair\n\n");
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
			case '1': criar_registro(arquivo);  // ./src/criar_registro.c
				break;
			case '2': //search();
				break;
			case '3': //update();
				break;
			case '4': //print();
				break;
			case '5': return 0;
				break;
			case '7':
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
			//RETURN VALUE fgetc(3)
			//	fgetc(), getc(), and getchar() return the character read as an
			//	unsigned char cast to an int or EOF on end of file or error.
		}
	}
	return EXIT_SUCCESS;
}

void ler_entrada(int tamanho, char entrada[tamanho])
{
	validar_entrada :
	while (fgets(entrada,tamanho,stdin) == NULL)
	{
		// fgets retorna NULL quando ocorre:
		//     erro de leitura
		//     eof antes da leitura de caracteres 
		if (feof(stdin))
		{
			fprintf(stderr,"\n"
				"    end of file occurs while no characters have been read\n"	
				"    end-of-file indicator is set for the stream\n\n"
			);
		}
		if (ferror(stdin))
		{
			fprintf(stderr,"\n"
				"    read error\n"
				"    error indicator is set for the stream\n\n"
			);

		}
		clearerr(stdin);	

		PRINT_STR(PURPLE,"tente novamente: ");
	}

    // remover \n (\n\r ou \r) da string que armazena a entrada do usuário
	int i = 0;
	for (i=0; i<tamanho; i++)
	{
		if (entrada[i] == '\n' || entrada[i] == '\r') 
		{
			entrada[i] = '\0';
			break;
		}
	}

	// garantir que a string tenha ao menos um caractere
	if (i==0)
	{
		fprintf(stderr,
			"entrada <RET> inválida\n\n"
		);
		PRINT_STR(PURPLE,"tente novamente: ");

		goto validar_entrada;
	}
	//PRINT_DEBUG("entrada: EOF\n");
	//exit(EXIT_SUCCESS);  // ^D termina a execução
}
