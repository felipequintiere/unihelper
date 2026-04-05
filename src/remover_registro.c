#include <stdio.h>
#include <stdlib.h>

#include "../include/types.h"
#include "../include/macros.h"
#include "../include/util.h"
#include "../include/remover_registro.h"
#include "../include/ler_entrada.h"

void remover_registro(const char * const arquivo)
{
    char entrada[ENTRADA_LEN+1];
    int id = -1;

    if (id_unico_prox(arquivo) == 0)
    {
        PRINT_STR(RED,"\nnão há dados armazenados!\n");
        return;
    }

    system("clear||cls");
    PRINT_STR(PURPLE,"REMOVENDO REGISTRO:\n");
    PRINT_STR(GREEN,"selecione o id único: ");
    for (;;)
    {
        ler_entrada(ENTRADA_LEN+1,entrada);
        if (sscanf(entrada,"%d",&id) == 1)
        {
            if (id >= id_unico_prox(arquivo) || id < 0)
            {
                PRINT_STR(RED,"\n"
                    "id único '%d' inválido!\n"
                    "tente novamente: ",
                id);
            }
            else
                break;
        }
    }



    Membro *membro = (Membro*) malloc(sizeof(Membro));

    // escreve do aquivo binário para o registro na memória
    arquivo_para_registro(membro,id,arquivo);

    if (membro->status_de_validacao == 0)
    {
        PRINT_STR(RED,"\nO REGISTRO JÁ HAVIA SIDO REMOVIDO\n");
    }
    else
    {
        //mostrar_registro(membro);
        PRINT_STR(RED,"\nO REGISTRO FOI REMOVIDO\n");
        membro->status_de_validacao = 0;
    }
    registro_para_arquivo(membro,id,arquivo);
}


