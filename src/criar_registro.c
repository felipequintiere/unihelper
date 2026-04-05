#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/util.h"
#include "../include/ler_entrada.h"
#include "../include/criar_registro.h"

void criar_registro(const char * const arquivo)
{
	static Membro membro = { .nome = {0} };
	char entrada[ENTRADA_LEN+1];

	system("clear||cls");
	PRINT_STR(PURPLE,"CRIANDO REGISTRO:\n");


	PRINT_STR(GREEN,"nome completo: ");
	ler_entrada(NOME_LEN+1,membro.nome); // espera char* (não signed char*)

	PRINT_STR(GREEN,"n° de disciplinas: ");
	for (;;) {
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d", &membro.numero_de_disciplinas) == 1) {
			break;
		}
		PRINT_STR(RED,"\ntente novamente: ");
	}

	PRINT_STR(GREEN,"grade: ");
	PRINT_STR(GREEN,"\n");

	PRINT_STR(GREEN,"aluno(0) ou professor(1): ");
	ler_tipo:
	for (;;)
	{
		int tmp;
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d",&tmp) == 1)
		{
			membro.tipo = tmp;
			break;
		}

		PRINT_STR(RED,"\ntente novamente: ");
	}

	switch (membro.tipo)
	{
		case ALUNO:
		{
			PRINT_DEBUG("tipo ALUNO\n");
			PRINT_STR(GREEN,"matrícula: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%llu", &membro.dados.aluno.matricula) == 1)
					break;

				PRINT_STR(RED,"\ntente novamente: ");
			}

			PRINT_STR(GREEN,"período: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%hu", &membro.dados.aluno.periodo) == 1)
					break;

				PRINT_STR(RED,"\ntente novamente: ");
			}
			break;
		}

		case PROFESSOR:
		{
			PRINT_DEBUG("tipo PROFESSOR\n");
			PRINT_STR(GREEN,"registro: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%llu",&membro.dados.professor.registro)==1)
					break;

				PRINT_STR(RED,"\ntente novamente: ");
			}

			PRINT_STR(GREEN,"salário: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%f",&membro.dados.professor.salario)==1)
					break;

				PRINT_STR(RED,"\ntente novamente: ");
			}
			break;
		}

		default:
			PRINT_STR(RED,
				"'%d' opção inválida!\n"
				"tente novamente: ",
				membro.tipo
			);
			goto ler_tipo;
	}

	membro.id_unico = id_unico_prox(arquivo);
	membro.status_de_validacao = 1; //true

	Membro *nmembro = &membro;	
	registro_para_arquivo(nmembro, nmembro->id_unico, arquivo);
}
