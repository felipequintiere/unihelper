
// O que acontece ao retirar o include da biblioteca
// stdbool desse header (types.h)?
//
// Se houver um '#include <stdbool.h>' no main.c, nada
// de atípico ocorre. Entretanto, se não existir um
// include no main.c ou(inclusivo) nesse arquivo, a
// seguinte mensagem será mostrada:
// ```
// $ make
// gcc -Wall -Wextra -Werror -O1   -c -o main.o main.c
// In file included from main.c:7:
// types.h:27:9: error: unknown type name ‘bool’
//    27 |         bool status_de_validacao;      // indicador de remoção
//       |         ^~~~
// types.h:1:1: note: ‘bool’ is defined in header ‘<stdbool.h>’; this is probably fixable by adding ‘#include <stdbool.h>’
//   +++ |+#include <stdbool.h>
//     1 |
// make: *** [<builtin>: main.o] Error 1
// ```
#ifndef INCLUDE_STDBOOL
#define INCLUDE_STDBOOL
#include <stdbool.h>
#endif

#define TAMANHO_NOME 64
#define DIAS 5
#define TURNOS 18

typedef struct {    // ESTRUTURA ALUNO
	unsigned long long matricula;
	unsigned int periodo;
} Dados_aluno;

typedef struct {    // ESTRUTURA PROFESSOR
	unsigned long long registro;
	float salario;
} Dados_professor;

typedef struct {    // ESTRUTRURA COMUM ENTRE OS TIPOS
	bool status_de_validacao;      // indicador de remoção
	unsigned int id_unico;         // gerado automaticamente

	signed char nome[TAMANHO_NOME+1];
	unsigned int numero_de_disciplinas;
	unsigned int grade[DIAS][TURNOS];
	// grade de horários [i][j]
	//     i: dias da semana (seg <-> sex)
	//     j: horários (m1 <-> t3 <-> n6)
	// nota: os elementos são os códigos de disciplinas

	enum {ALUNO = 0, PROFESSOR} tipo;
	union {
		Dados_aluno aluno;
		Dados_professor professor;
	} dados;
} Membro;

