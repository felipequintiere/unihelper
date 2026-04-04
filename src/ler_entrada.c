#include <stdio.h>
#include "../include/macros.h"
#include "../include/ler_entrada.h"

void ler_entrada(int tamanho, char entrada[tamanho])
{
	validar_entrada :
	while (fgets(entrada,tamanho,stdin) == NULL)
	{
		// fgets retorna NULL quando ocorre:
		//     erro de leitura
		//     eof antes da leitura de caracteres 
		if (feof(stdin))
		{
			fprintf(stderr,"\n"
				"    end of file occurs while no characters have been read\n"	
				"    end-of-file indicator is set for the stream\n\n"
			);
		}
		if (ferror(stdin))
		{
			fprintf(stderr,"\n"
				"    read error\n"
				"    error indicator is set for the stream\n\n"
			);

		}
		clearerr(stdin);	

		PRINT_STR(PURPLE,"tente novamente: ");
	}

    // remover \n (\n\r ou \r) da string que armazena a entrada do usuário
	int i = 0;
	for (i=0; i<tamanho; i++)
	{
		if (entrada[i] == '\n' || entrada[i] == '\r') 
		{
			entrada[i] = '\0';
			break;
		}
	}

	// garantir que a string tenha ao menos um caractere
	if (i==0)
	{
		fprintf(stderr,
			"entrada <RET> inválida\n\n"
		);
		PRINT_STR(PURPLE,"tente novamente: ");

		goto validar_entrada;
	}
	//PRINT_DEBUG("entrada: EOF\n");
	//exit(EXIT_SUCCESS);  // ^D termina a execução
}
