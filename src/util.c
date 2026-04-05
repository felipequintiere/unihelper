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
