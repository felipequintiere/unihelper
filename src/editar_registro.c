#include <stdio.h>
#include <stdlib.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/ler_entrada.h"


void editar_registro()
{
	char entrada[ENTRADA_LEN+1];
	int opcao = -1;

	system("clear||cls");
	PRINT_STR(PURPLE, "\n EDITANDO REGISTRO:\n");

	PRINT_STR(GREEN," selecione o id do registro a ser editado: ");
	ler_entrada(ENTRADA_LEN+1,entrada);
	for (;;) {
		ler_entrada(ENTRADA_LEN+1,entrada);
		if (sscanf(entrada,"%d",&opcao) == 1) {
			break;
		}
		PRINT_STR(RED, "\n tente novamente: ");
	}


}







