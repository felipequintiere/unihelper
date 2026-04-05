#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// considere usar
// #include <stdint.h>
// #include <inttypes.h>  // for format specifiers
// note: enums can have different sizes

#include <stdbool.h>

#include "./include/macros.h"
#include "./include/types.h"
#include "./include/util.h"
#include "./include/flags.h"
#include "./include/ler_entrada.h"
#include "./include/criar_registro.h"

#define ARQUIVO_DADOS "./dados.bin"


void editar_registro(const char * const);
void arquivo_para_registro(Membro *, int, const char * const);
void mostrar_registro(Membro *);

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
			case '1': criar_registro(arquivo);  // ./src/criar_registro.c
				break;
			case '2': editar_registro(arquivo);
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

//stdio
//macro
//util
void editar_registro(const char * const arquivo)
{
	char entrada[ENTRADA_LEN+1];
	int id = -1;
	
	if (id_unico_prox(arquivo) == 0)
	{
		PRINT_STR(RED,"\nnão há dados armazenados!\n");
		return;
	}

	system("clear||cls");
	PRINT_STR(PURPLE, "\nEDITANDO REGISTRO:\n");
	PRINT_STR(GREEN,"selecione o id único do registro a ser editado: ");
	for (;;)
	{
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d",&id) == 1)
		{
			if (id >= id_unico_prox(arquivo) || id < 0)
			{
				PRINT_STR(RED,"\n"
					"id único '%d' inválido!\n"
					"tente novamente: ",
				id);
			}	
			else
				break;
		}
	}



	Membro *membro = (Membro*) malloc(sizeof(Membro));
	// escreve do aquivo para o registro
	arquivo_para_registro(membro,id,arquivo);
	mostrar_registro(membro);



	PRINT_STR(GREEN,"\nmodificar: ");
	PRINT_STR(PURPLE,"\n\n"
	"[1] nome\n"
	"[2] matrícula\n"
	"[3] período\n"
	"[4] n° de disciplinas\n"
	"[5] grade\n"
	"[6-7] sair\n\n");
	PRINT_STR(GREEN,"escolha uma opção: ");
	for (;;)
	{
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d",&id) == 1)
		{
				break;
		}
	}

	switch (entrada[0])
	{
		case '1': break;
			break;
		case '2': break;
			break;
		case '3': break;
			break;
		case '4': break;
			break;
		case '5': break;
			break;
		case '7':
				  return;
		default:
			fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
	}
}


void arquivo_para_registro(Membro *membro, int id, const char * const arquivo)
{
	FILE *fp;
	if ((fp = fopen(arquivo,"rb")) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	fseek(fp, (REGISTRO_LEN * (long) id), SEEK_SET);



	fread(&membro->id_unico,
		sizeof(membro->id_unico),1,fp);

	fread(&membro->status_de_validacao,
		sizeof(membro->status_de_validacao),1,fp);

	fread(&membro->nome,
		sizeof(membro->nome),1,fp);

	fread(&membro->numero_de_disciplinas,
		sizeof(membro->numero_de_disciplinas),1,fp);

	fread(&membro->grade,
		sizeof(membro->grade),1,fp);

	fread(&membro->tipo, sizeof(membro->tipo), 1, fp);
	if (membro->tipo == ALUNO)
	{
		fread(&membro->dados.aluno.matricula,
			sizeof(membro->dados.aluno.matricula),1,fp);

		fread(&membro->dados.aluno.periodo,
			sizeof(membro->dados.aluno.periodo),1,fp);
	}
	else if (membro->tipo == PROFESSOR)
	{
		fread(&membro->dados.professor.registro,
			sizeof(membro->dados.professor.registro),1,fp);
		fread(&membro->dados.professor.salario,
			sizeof(membro->dados.professor.salario),1,fp);
	}

	fclose(fp);
}

void mostrar_registro(Membro *membro)
{
	printf("\n");
	PRINT_STR(BLUE,"tipo: %s\n",((membro->tipo) ? "professor" : "aluno"));
	PRINT_STR(BLUE,"nome: %s\n",membro->nome);

	if (membro->tipo == ALUNO)
	{
		PRINT_STR(BLUE,"matrícula: %llu\n",membro->dados.aluno.matricula);
		PRINT_STR(BLUE,"período: %hd\n",membro->dados.aluno.periodo);
	}
	else if (membro->tipo == PROFESSOR)
	{
		PRINT_STR(BLUE,"registro: %llu\n",membro->dados.professor.registro);
		PRINT_STR(BLUE,"salário: %f\n",membro->dados.professor.salario);
	}

	PRINT_STR(BLUE,"n° de disciplinas: %d\n",membro->numero_de_disciplinas);
	PRINT_STR(BLUE,"id único: %u\n",membro->id_unico);
	//PRINT_STR(BLUE,"status de validação: %hd\n",membro->status_de_validacao);
	//grade
}
