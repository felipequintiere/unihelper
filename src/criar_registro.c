#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/criar_registro.h"

void determinar_o_tamanho_da_struct(Membro*); // só é usada aqui

Membro* criar_registro(const char * const arquivo)
{
	system("clear||cls");

	static Membro membro = { .nome = {0} };

#if defined(DEBUG) && DEBUG==1
	determinar_o_tamanho_da_struct(&membro);
#endif

	// criar uma função para evitar o ^d, pois sem isso,
	// a aplicação ainda continua escrevendo para o arquivo de dados
	PRINT_STR(PURPLE, "\n CRIANDO REGISTRO:\n");

	PRINT_STR(GREEN, " nome completo: ");
	fgets(membro.nome,TAMANHO_NOME+1,stdin); // espera 'char *' e não 'signed char *'

	PRINT_STR(GREEN, " n° de disciplinas: ");
	scanf("%d*c", &membro.numero_de_disciplinas);

	PRINT_STR(GREEN, " grade: ");
	// gerar_grade()

	PRINT_STR(GREEN, " aluno(0) ou professor(1): ");
	ler_tipo: scanf("%d*c", (int *) &membro.tipo);
	switch (membro.tipo)
	{
		case ALUNO:
		{
			PRINT_DEBUG("tipo ALUNO\n");

			PRINT_STR(GREEN, " matrícula: ");
			scanf("%llu*c", &membro.dados.aluno.matricula);
			PRINT_STR(GREEN, " período: ");
			scanf("%hu*c", &membro.dados.aluno.periodo);
			break;
		}

		case PROFESSOR:
		{
			PRINT_DEBUG("tipo PROFESSOR\n");

			PRINT_STR(GREEN, " registro: ");
			scanf("%llu", &membro.dados.professor.registro);
			PRINT_STR(GREEN, " salário: ");
			scanf("%f", &membro.dados.professor.salario);
			break;
		}

		default:
			PRINT_STR(RED," '%d' opção inválida!\n",membro.tipo);
			PRINT_STR(RED," tente novamente: ");
			goto ler_tipo;
	}

	membro.status_de_validacao = true;
	//membro.id_unico = 1; ///////////////////////////////////////////////////////////////////////////////////////////////////

	
	FILE *fp;
	if ((fp = fopen(arquivo,"ab+")) == NULL)
	{
		exit(EXIT_FAILURE);
	}

	fwrite(&membro.status_de_validacao,   sizeof(membro.status_de_validacao), 1, fp);
	fwrite(&membro.id_unico,              sizeof(membro.id_unico), 1, fp);
	fwrite(&membro.nome,                  sizeof(membro.nome), 1, fp);
	fwrite(&membro.numero_de_disciplinas, sizeof(membro.numero_de_disciplinas), 1, fp);
	fwrite(&membro.grade,                 sizeof(membro.grade), 1, fp);

	fwrite(&membro.tipo, sizeof(membro.tipo), 1, fp);
	if (membro.tipo == ALUNO)
	{
		fwrite(&membro.dados.aluno.matricula, sizeof(membro.dados.aluno.matricula), 1, fp);
		fwrite(&membro.dados.aluno.periodo,   sizeof(membro.dados.aluno.periodo), 1, fp);
	}
	else if (membro.tipo == PROFESSOR)
	{
		fwrite(&membro.dados.professor.registro, sizeof(membro.dados.professor.registro), 1, fp);
		fwrite(&membro.dados.professor.salario,  sizeof(membro.dados.professor.salario), 1, fp);
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

// debug
void determinar_o_tamanho_da_struct(Membro *membro)
{
#define PRINT_SIZE(variavel, tipo) \
	( ((variavel)+=sizeof(tipo)) , \
	  printf(RED" %-3zu : "#tipo" \n"RESET, sizeof(tipo)) )
/*
	do { \
		(variavel) += sizeof((tipo)); \
		printf(RED" %-3zu : "#tipo" \n"RESET, sizeof(tipo)); \
	} while(0)
*/

    size_t size_final = 0;
	printf("\n comum:\n");
    PRINT_SIZE(size_final, membro->status_de_validacao);
    PRINT_SIZE(size_final, membro->id_unico);
    PRINT_SIZE(size_final, membro->nome);
    PRINT_SIZE(size_final, membro->numero_de_disciplinas);
    PRINT_SIZE(size_final, membro->grade);
	PRINT_SIZE(size_final, membro->tipo);
	// nota: está passando uma expressão cujo tipo será inferido; 
	// passar diretamente o membro da struct para o sizeof previne
	// a leitura de tamanhos distintos caso o tipo do membro da 
	// struct seja alterado

    size_t size_aluno = 0;
	printf("\n aluno:\n");
    PRINT_SIZE(size_aluno, membro->dados.aluno.matricula);
    PRINT_SIZE(size_aluno, membro->dados.aluno.periodo);

    size_t size_professor = 0;
	printf("\n professor: \n");
    PRINT_SIZE(size_professor, membro->dados.professor.registro);
    PRINT_SIZE(size_professor, membro->dados.professor.salario);

	size_final += ((size_aluno > size_professor) ? size_aluno : size_professor);
	PRINT_DEBUG("\n tamanho efetivo do registro em bytes: %zu",size_final);
#undef PRINT_SIZE
}
