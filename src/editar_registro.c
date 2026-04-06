#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/util.h"
#include "../include/criar_registro.h"
#include "../include/editar_registro.h"
#include "../include/ler_entrada.h"

void editar_registro(const char * const arquivo)
{
	char entrada[ENTRADA_LEN+1];
	int id = -1;
	
	if (id_unico_prox(arquivo) == 0)
	{
		PRINT_STR(RED,"\nnão há dados armazenados em '%s'\n",arquivo);
		return;
	}

	system("clear||cls");
	PRINT_STR(PURPLE,"EDITANDO REGISTRO:\n");

	//PRINT_STR(YELLOW,"\nINFORMAÇÕES DO REGISTRO:\n");
	id = buscar_registro_id(arquivo);
	// se o retorno de buscar_registro_id() for inválido,
	// retorna para main()
	if (id == -1)
		return;



	Membro *membro = (Membro*) malloc(sizeof(Membro));
	arquivo_para_registro(membro,id,arquivo);

	if(membro->status_de_validacao == 0)
	{
		int opcao = -1;
		PRINT_STR(GREEN,"\n\ncriar outro registro nessa posição?\n");
		PRINT_STR(CYAN,"\n"
			"[0] não\n"
			"[1] sim\n"
		);
		PRINT_STR(PURPLE,"\nescolha uma opção: ");
		for (;;)
		{
			ler_entrada(ENTRADA_LEN+1,entrada);
			if (sscanf(entrada,"%d", &opcao) == 1)
			{
				if (opcao == 0)
					break;
				else if (opcao == 1)
				{
					criar_registro(membro->id_unico,arquivo);
					break;
				}
				else
					PRINT_STR(RED, "\ntente novamente: ");
			}
		}
		return;
	}



	PRINT_STR(GREEN,"\n\neditar:");
	if (membro->tipo == ALUNO)
	{
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
			case '1':
			{
    			PRINT_STR(GREEN, "nome completo: ");
    			ler_entrada(NOME_LEN+1,membro->nome);
				break;
			}
			case '2':
			{
				PRINT_STR(GREEN, "matrícula: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%llu", &membro->dados.aluno.matricula) == 1)
						break;

					PRINT_STR(RED, "\ntente novamente: ");
				}
				break;
			}
			case '3':
			{
				PRINT_STR(GREEN, "período: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%hu", &membro->dados.aluno.periodo) == 1)
						break;

					PRINT_STR(RED, "\ntente novamente: ");
				}
				break;
			}
			case '4':
			{
				PRINT_STR(GREEN, "n° de disciplinas: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%d", &membro->numero_de_disciplinas) == 1)
						break;

					PRINT_STR(RED, "\n tente novamente: ");
				}
				break;
			}
			case '5':
			{
				PRINT_STR(GREEN, "grade:\n");
				gerar_grade(membro);
				break;
			}
			case '6':
			case '7':
					  return;
			default:
				fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
		}
	}
	else if (membro->tipo == PROFESSOR)
	{
		PRINT_STR(PURPLE,"\n\n"
		"[1] nome\n"
		"[2] identificação\n"
		"[3] salário\n"
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
			case '1':
			{
    			PRINT_STR(GREEN, "nome completo: ");
				ler_entrada(NOME_LEN+1,membro->nome);
				break;
			}
			case '2':
			{
				PRINT_STR(GREEN, "identificação: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%llu", &membro->dados.professor.registro) == 1)
						break;

					PRINT_STR(RED, "\ntente novamente: ");
				}
				break;
			}
			case '3':
			{
				PRINT_STR(GREEN, "salário: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%f", &membro->dados.professor.salario) == 1)
						break;

					PRINT_STR(RED, "\ntente novamente: ");
				}
				break;
			}
			case '4':
			{
				PRINT_STR(GREEN, "n° de disciplinas: ");
				for (;;)
				{
					ler_entrada(ENTRADA_LEN+1,entrada);
					if (sscanf(entrada,"%d", &membro->numero_de_disciplinas) == 1)
						break;

					PRINT_STR(RED, "\n tente novamente: ");
				}
				break;
			}
			case '5':
			{
				PRINT_STR(GREEN, "grade:\n");
				gerar_grade(membro);
				break;
			}
			case '6':
			case '7':
					  return;
			default:
				fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
		}
	}



	PRINT_STR(BLUE,"\n\nNOVA VERSÃO DO REGISTRO\n");
	mostrar_registro(membro);
	registro_para_arquivo(membro,membro->id_unico,arquivo);
	PRINT_DEBUG("id_unico: %d\n",membro->id_unico);
}
