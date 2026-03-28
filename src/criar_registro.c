#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/criar_registro.h"

void determinar_o_tamanho_da_struct(Membro*);

Membro* criar_registro(const char * const arquivo)
{
	system("clear||cls");

	static Membro membro = { .nome = {0} };
#if defined(DEBUG) && DEBUG==1
	determinar_o_tamanho_da_struct(&membro);
#endif

	print_str(PURPLE, "\n CRIANDO REGISTRO:\n");

	print_str(GREEN, " nome completo: ");
	scanf("%s", membro.nome); // não lê a linha completa, para no primeiro white-space
	print_str(GREEN, " n° de disciplinas: ");
	scanf("%d", &membro.numero_de_disciplinas);
	print_str(GREEN, " grade: ");
	// gerar_grade()

	print_str(GREEN, " aluno(0) ou professor(1): ");
	ler_tipo: scanf("%d", (int *) &membro.tipo);
	switch (membro.tipo)
	{
		case ALUNO: {
			DEBUG_PRINT("tipo ALUNO\n");

			print_str(GREEN, " matrícula: ");
			scanf("%llu", &membro.dados.aluno.matricula);
			print_str(GREEN, " período: ");
			scanf("%hu", &membro.dados.aluno.periodo);
			break;
		}

		case PROFESSOR: {
			DEBUG_PRINT("tipo PROFESSOR\n");

			print_str(GREEN, " registro: ");
			scanf("%llu", &membro.dados.professor.registro);
			print_str(GREEN, " salário: ");
			scanf("%f", &membro.dados.professor.salario);
			break;
		}

		default:
			print_str(RED," '%d' opção inválida!\n",membro.tipo);
			print_str(RED," tente novamente: ");
			goto ler_tipo;
	}

	membro.status_de_validacao = true;
	//membro.id_unico = 1; ///////////////////////////////////////////////////////////////////////////////////////////////////

	
	FILE *fp = fopen(arquivo, "ab+");

	fwrite(&membro.status_de_validacao, sizeof(membro.status_de_validacao), 1, fp);
	fwrite(&membro.id_unico, sizeof(membro.id_unico), 1, fp);
	fwrite(&membro.nome, sizeof(membro.nome), 1, fp);
	fwrite(&membro.numero_de_disciplinas, sizeof(membro.numero_de_disciplinas), 1, fp);
	fwrite(&membro.grade, sizeof(membro.grade), 1, fp);

	fwrite(&membro.tipo, sizeof(membro.tipo), 1, fp);
	if (membro.tipo == ALUNO)
	{
		fwrite(&membro.dados.aluno.matricula, sizeof(membro.dados.aluno.matricula), 1, fp);
		fwrite(&membro.dados.aluno.periodo, sizeof(membro.dados.aluno.periodo), 1, fp);
	}
	else if (membro.tipo == PROFESSOR)
	{
		fwrite(&membro.dados.professor.registro, sizeof(membro.dados.professor.registro), 1, fp);
		fwrite(&membro.dados.professor.salario, sizeof(membro.dados.professor.salario), 1, fp);
	}
/*
       size_t fwrite(const void ptr[restrict .size * .nmemb],
                    size_t size, size_t nmemb,
                    FILE *restrict stream);
       [...]
       On  success,  fread()  and fwrite() return the number of items
       read or written.  This  number  equals  the  number  of  bytes
       transferred  only  when size is 1.  If an error occurs, or the
       end of the file is reached, the return value is a  short  item
       count (or zero).

*/
	fclose(fp);

	return &membro;
}

void determinar_o_tamanho_da_struct(Membro *membro)
{
#define print_size(variavel, tipo) \
    do { \
        (variavel) += sizeof((tipo)); \
        printf(RED" %-3zu : "#tipo" \n"RESET, sizeof(tipo)); \
    } while(0)

    size_t size_final = 0;
	printf("\n comum:\n");
    print_size(size_final, membro->status_de_validacao);
    print_size(size_final, membro->id_unico);
    print_size(size_final, membro->nome);
    print_size(size_final, membro->numero_de_disciplinas);
    print_size(size_final, membro->grade);
	print_size(size_final, membro->tipo);

    size_t size_aluno = 0;
	printf("\n aluno:\n");
    print_size(size_aluno, membro->dados.aluno.matricula);
    print_size(size_aluno, membro->dados.aluno.periodo);

    size_t size_professor = 0;
	printf("\n professor: \n");
    print_size(size_professor, membro->dados.professor.registro);
    print_size(size_professor, membro->dados.professor.salario);

	size_final += ((size_aluno > size_professor) ? size_aluno : size_professor);
	DEBUG_PRINT("\n tamanho efetivo do registro em bytes: %zu",size_final);
}
