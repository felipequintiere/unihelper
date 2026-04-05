#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/util.h"

long int id_unico_prox(const char * const arquivo)
{
	FILE *fp;
	if ((fp = fopen(arquivo,"ab+")) == NULL)
	{
		exit(EXIT_FAILURE);
	}

	// necessário porque não houve leitura nem escrita
	// antes de usar o ftell()
	fseek(fp, 0L, SEEK_END);
	long int id = ftell(fp)/REGISTRO_LEN;
	fclose(fp);

	return id;
}

void registro_para_arquivo(Membro *membro, int id, const char * const arquivo)
{
	FILE *fp;
	if ((fp = fopen(arquivo,"r+b")) == NULL)
	{
		exit(EXIT_FAILURE);
	}
	fseek(fp, (REGISTRO_LEN * (long) id), SEEK_SET);



	fwrite(&membro->id_unico,
		sizeof(membro->id_unico),1,fp);

	fwrite(&membro->status_de_validacao,
		sizeof(membro->status_de_validacao),1,fp);

	//fread(&membro->nome,sizeof(membro->nome),1,fp);
	fwrite(membro->nome,sizeof(char),NOME_LEN+1,fp);

	fwrite(&membro->numero_de_disciplinas,
		sizeof(membro->numero_de_disciplinas),1,fp);

	fwrite(&membro->grade,
		sizeof(membro->grade),1,fp);

	fwrite(&membro->tipo, sizeof(membro->tipo), 1, fp);
	if (membro->tipo == ALUNO)
	{
		fwrite(&membro->dados.aluno.matricula,
			sizeof(membro->dados.aluno.matricula),1,fp);

		fwrite(&membro->dados.aluno.periodo,
			sizeof(membro->dados.aluno.periodo),1,fp);
	}
	else if (membro->tipo == PROFESSOR)
	{
		fwrite(&membro->dados.professor.registro,
			sizeof(membro->dados.professor.registro),1,fp);
		fwrite(&membro->dados.professor.salario,
			sizeof(membro->dados.professor.salario),1,fp);
	}

	// escrever zeros no espaço restante
    int t_prof = (int) REGISTRO_PROFESSOR;
    int t_alun = (int) REGISTRO_ALUNO;
    int t_mod_dif = (t_prof>=t_alun ? t_prof-t_alun : t_alun-t_prof);
    for (int i=0; i<(t_mod_dif); i++)
    {
        fputc(0,fp);
    }

	fclose(fp);
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

	//fread(&membro->nome,sizeof(membro->nome),1,fp);
	fread(membro->nome,sizeof(char),NOME_LEN+1,fp);

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
	if(membro->status_de_validacao == 0)
	{
		PRINT_STR(RED,
			"REGISTRO DELETADO!\n"
			"==================\n"
			"==================\n"
			"==================\n"
			"==================\n"
			"==================\n"
			"==================\n"
		);
	}
	else if(membro->status_de_validacao == 1)
	{
		PRINT_STR(BLUE,"tipo:          %s\n",((membro->tipo) ? "professor" : "aluno"));
		PRINT_STR(BLUE,"nome:          %s\n",membro->nome);

		if (membro->tipo == ALUNO)
		{
			PRINT_STR(BLUE,"matrícula:     %llu\n",membro->dados.aluno.matricula);
			PRINT_STR(BLUE,"período:       %hd\n",membro->dados.aluno.periodo);
		}
		else if (membro->tipo == PROFESSOR)
		{
			PRINT_STR(BLUE,"identificação: %llu\n",membro->dados.professor.registro);
			PRINT_STR(BLUE,"salário:       %.2f\n",membro->dados.professor.salario);
		}

		PRINT_STR(BLUE,"n disciplinas: %d\n",membro->numero_de_disciplinas);
		PRINT_STR(BLUE,"id único:      %u\n",membro->id_unico);
		//PRINT_STR(BLUE,"status de validação: %hd\n",membro->status_de_validacao);
		//grade
	}
}

