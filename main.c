#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include "./include/macros.h"
#include "./include/types.h"
#include "./include/flags.h"

#define TAM_INPUT 16
#define TAM_REGISTRO 438L
#define ARQUIVO_DADOS "./dados.bin"

#define print_str(color,str, ...) \
	printf(color str RESET, ##__VA_ARGS__)

static Membro* criar_registro(void);

int main(int argc, char *argv[])
{
	static char *arquivo = ARQUIVO_DADOS;

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
				printf(
				"error: a value is required for '--file <DATA_FILE>' but none "
			   	"was supplied\n\nFor more information, try '--help'."
				);
				exit(EXIT_SUCCESS);
			}
			else if (argc > 3)
			{
				printf("error: unrecognized subcommand '%s'",argv[3]);
				printf("\n\nFor more information, try '--help'.");
				exit(EXIT_SUCCESS);
			}
			else
			{
				// armazenar o nome do arquivo escolhido pelo usuário (-f)
				arquivo = argv[2];
				DEBUG_PRINT("%s\n",arquivo);  // remova o próximo clear||cls
			}
		}
		else
		{
			flag_invalid(argv);  // passa todos os argumentos
			exit(EXIT_SUCCESS);
		}
	}

	//system("clear||cls");
	int option;
	for (;;)
	{
		print_str(CYAN,"\n"
		" [1] criar registro\n"
		" [2] editar registro\n"
		" [3] remover registro\n"
		" [4] buscar registro por id\n"
		" [5] buscar registro por nome\n"
		" [6] listar registros\n"
		" [7] sair\n\n");
		print_str(PURPLE," Escolha uma opção: ");

		// se o usuário inserir ^D
		if ((option = fgetc(stdin)) == EOF)
		{
			DEBUG_PRINT("entrada: EOF\n");

			//exit(EXIT_SUCCESS); // ^D termina a execução
			clearerr(stdin);    // reseta o estado EOF de stdin
			continue;
		}

		// para descartar o resto da entrada
		int ch;
		while ((ch = fgetc(stdin)) != '\n' && ch != EOF)
			;

		//         scanf(" %c", &option); 
		// nota:
		// Em uma entrada como "abcde...", esse scanf leria o
		// primeiro caractere, porém, os demais ficariam dentro
		// do input buffer. Consequentemente, as próximas
		// chamadas do scanf leriam esses valores armazenados no
		// buffer 

		switch (option)
		{
			case '1': criar_registro();
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
				print_str(RED," '%c' opção inválida!\n",option);
				//RETURN VALUE fgetc(3)
				//	fgetc(), getc(), and getchar() return the character read as an
				//	unsigned char cast to an int or EOF on end of file or error.
		}
	}
	return EXIT_SUCCESS;
}

static Membro* criar_registro(void)
{
	static Membro membro;

	system("clear||cls");
	print_str(RED, "\n CRIANDO REGISTRO:\n");

	print_str(GREEN, " nome completo: ");
	scanf("%s", membro.nome); // não lê a linha completa, para no primeiro white-space
	print_str(GREEN, " n° de disciplinas: ");
	scanf("%u", &membro.numero_de_disciplinas);

	// gerar_grade()

	print_str(GREEN, " aluno(0) ou professor(1): ");
	ler_tipo: scanf("%d", (int *) &membro.tipo);

	switch (membro.tipo)
	{
		case ALUNO:
			//criar_registro_aluno();
			DEBUG_PRINT("tipo ALUNO\n");
			break;
		case PROFESSOR:
			//criar_registro_professor();
			DEBUG_PRINT("tipo PROFESSOR\n");
			break;
		default:
			print_str(RED," '%d' opção inválida!\n",membro.tipo);
			print_str(RED," tente novamente: ");
			goto ler_tipo;
	}

	return &membro;
}
