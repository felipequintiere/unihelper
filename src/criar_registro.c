#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/util.h"
#include "../include/ler_entrada.h"
#include "../include/criar_registro.h"

void criar_registro(int prox_id_unico, const char * const arquivo)
{
	static Membro membro = { .nome = {0} };
	char entrada[ENTRADA_LEN+1];

	system("clear||cls");
	PRINT_STR(PURPLE,"CRIANDO REGISTRO:\n");

	PRINT_STR(GREEN,"nome completo: ");
	ler_entrada(NOME_LEN+1,membro.nome); // espera char* (não signed char*)

	PRINT_STR(GREEN,"aluno(0) ou professor(1): ");
	for (;;)
	{
		int tmp;
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d",&tmp) == 1)
		{
			if (tmp == ALUNO || tmp == PROFESSOR)
			{
				membro.tipo = tmp;
				break;
			}
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
	}

	PRINT_STR(GREEN,"n° de disciplinas: ");
	for (;;) {
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d", &membro.numero_de_disciplinas) == 1) {
			break;
		}
		PRINT_STR(RED,"\ntente novamente: ");
	}

	PRINT_STR(GREEN,"grade:\n");
	gerar_grade(&membro);



	membro.id_unico = prox_id_unico;
	membro.status_de_validacao = 1; //true

	Membro *ptr_membro = &membro;	
	registro_para_arquivo(ptr_membro,prox_id_unico,arquivo);
}



void gerar_grade(Membro *membro)
{
	char entrada[ENTRADA_LEN+1];
	int codigo;
	int dia;
	int horario;

	PRINT_STR(BLUE,
		" nota:\n"
		"  1. insira '0' no prompt para retornar;\n"
		"  2. insira o código de disciplina '0' para excluir uma aula,\n"
		"  caso contrário, utilize um código de 5 dígitos;\n"
	);
	for(;;)
	{
		PRINT_STR(BLUE,"escolha o código da disciplina: ");
		for (;;)
		{
			ler_entrada(ENTRADA_LEN+1,entrada);
			if (sscanf(entrada,"%d",&codigo)==1)
				break;

			PRINT_STR(RED,"\ntente novamente: ");
		}

		PRINT_STR(CYAN,"escolha o dia da semana [1-5]: ");
		for (;;)
		{
			ler_entrada(ENTRADA_LEN+1,entrada);
			if (sscanf(entrada,"%d",&dia)==1)
				break;

			PRINT_STR(RED,"\ntente novamente: ");
		}
		if (dia == 0)
			break;


		for(;;)
		{
			PRINT_STR(YELLOW,"escolha o horário [1-18]: ");
			for(;;)
			{
				ler_entrada(ENTRADA_LEN+1,entrada);
				if (sscanf(entrada,"%d",&horario)==1)
					break;

				PRINT_STR(RED,"\ntente novamente: ");

			}
			if (horario >=1 && horario <= 18)
				membro->grade[dia-1][horario-1] = codigo;
			else if (horario == 0)
				break;
		}
	}
}
