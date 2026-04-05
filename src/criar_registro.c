#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/util.h"
#include "../include/ler_entrada.h"
#include "../include/criar_registro.h"

Membro* criar_registro(const char * const arquivo)
{
	static Membro membro = { .nome = {0} };
	char entrada[ENTRADA_LEN+1];

	system("clear||cls");
	PRINT_STR(PURPLE, "\n CRIANDO REGISTRO:\n");


	PRINT_STR(GREEN, " nome completo: ");
	ler_entrada(NOME_LEN+1,membro.nome); // espera char* (não signed char*)

	PRINT_STR(GREEN, " n° de disciplinas: ");
	for (;;) {
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d", &membro.numero_de_disciplinas) == 1) {
			break;
		}
		PRINT_STR(RED, "\n tente novamente: ");
	}

	PRINT_STR(GREEN, " grade: ");
	PRINT_STR(GREEN, "\n");

	PRINT_STR(GREEN, " aluno(0) ou professor(1): ");
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

		PRINT_STR(RED, "\n tente novamente: ");
	}

	switch (membro.tipo)
	{
		case ALUNO:
		{
			PRINT_DEBUG("tipo ALUNO\n");
			PRINT_STR(GREEN, " matrícula: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%llu", &membro.dados.aluno.matricula) == 1)
					break;

				PRINT_STR(RED, "\n tente novamente: ");
			}

			PRINT_STR(GREEN, " período: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%hu", &membro.dados.aluno.periodo) == 1)
					break;

				PRINT_STR(RED, "\n tente novamente: ");
			}
			break;
		}

		case PROFESSOR:
		{
			PRINT_DEBUG("tipo PROFESSOR\n");
			PRINT_STR(GREEN, " registro: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%llu",&membro.dados.professor.registro)==1)
					break;

				PRINT_STR(RED, "\n tente novamente: ");
			}

			PRINT_STR(GREEN, " salário: ");
			for (;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%f",&membro.dados.professor.salario)==1)
					break;

				PRINT_STR(RED, "\n tente novamente: ");
			}
			break;
		}

		default:
			PRINT_STR(RED,
				" '%d' opção inválida!\n"
				" tente novamente: ",
				membro.tipo
			);
			goto ler_tipo;
	}

	membro.id_unico = id_unico_prox(arquivo);
	membro.status_de_validacao = 1; //true



	FILE *fp;
	if ((fp = fopen(arquivo,"ab+")) == NULL)
	{
		exit(EXIT_FAILURE);
	}

	fwrite(&membro.id_unico,
		sizeof(membro.id_unico),1,fp);

	fwrite(&membro.status_de_validacao,
		sizeof(membro.status_de_validacao),1,fp);

	fwrite(&membro.nome,
		sizeof(membro.nome),1,fp);

	fwrite(&membro.numero_de_disciplinas,
		sizeof(membro.numero_de_disciplinas),1,fp);

	fwrite(&membro.grade,
		sizeof(membro.grade),1,fp);

	fwrite(&membro.tipo, sizeof(membro.tipo), 1, fp);
	if (membro.tipo == ALUNO)
	{
		fwrite(&membro.dados.aluno.matricula,
			sizeof(membro.dados.aluno.matricula),1,fp);

		fwrite(&membro.dados.aluno.periodo,
			sizeof(membro.dados.aluno.periodo),1,fp);
	}
	else if (membro.tipo == PROFESSOR)
	{
		fwrite(&membro.dados.professor.registro, sizeof(membro.dados.professor.registro),1,fp);
		fwrite(&membro.dados.professor.salario,  sizeof(membro.dados.professor.salario),1,fp);
	}


	int t_prof = (int) REGISTRO_PROFESSOR;
	int t_alun = (int) REGISTRO_ALUNO;
	int t_mod_dif = (t_prof>=t_alun ? t_prof-t_alun : t_alun-t_prof);
	for (int i=0; i<(t_mod_dif); i++) 
	{
		fputc(0,fp);
	}


	fclose(fp);
	return &membro;
}
