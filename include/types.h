#ifndef INCLUDE_TYPES
#define INCLUDE_TYPES

#include "./macros.h"

typedef struct {  // ESTRUTURA ALUNO
	unsigned long long matricula;
	unsigned short int periodo;
} Dados_aluno;

typedef struct {  // ESTRUTURA PROFESSOR
	unsigned long long registro;
	float salario;
} Dados_professor;

typedef struct {  // ESTRUTRURA COMUM ENTRE OS TIPOS
	//bool status_de_validacao;
	short int status_de_validacao;  // indicador de remoção
	unsigned int id_unico;  // gerado automaticamente

	//signed char nome[NOME_LEN+1];
	char nome[NOME_LEN+1]; // fgets espera 'char *' e não 'unsigned char*'
	int numero_de_disciplinas;
	int grade[DIAS][TURNOS];
	// grade de horários [i][j]
	//     i: dias da semana (seg <-> sex)
	//     j: horários (m1 <-> t3 <-> n6)
	// nota: os elementos são os códigos de disciplinas

	// nota: tamanho variável do tipo enum
	enum {ALUNO = 0, PROFESSOR} tipo;
	union {
		Dados_aluno aluno;
		Dados_professor professor;
	} dados;
	// nota: structs/unions anônimos são padrão apenas a partir 
	// do C11
} Membro;
#endif

