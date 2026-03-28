#include <stdio.h>
#include "../include/flags.h"

void flag_help(const char * const nome_do_programa)
{
    printf("Usage: %s [OPTION]... [FILE]...\n\n",nome_do_programa);
    printf(
	"  -f, --file <DATA_FILE>   path to data file\n"
    "  -v, --version     output version information and exit\n"
    "  -h, --help        display this help and exit\n");
}

void flag_version(const char * const nome_do_programa)
{
	printf("%s (c) 2026 %s, Inc.\n",
	nome_do_programa,nome_do_programa);
	printf("Compiled on %s at %s\n", __DATE__, __TIME__);
}

void flag_invalid(char * const *parametros)
{
	// passando o nome do programa e a primeira flag
	printf("%s: invalid option -- '%s'\n",
		parametros[0], parametros[1]);  // nome e primeira flag 
	printf("Try '%s --help' for more information.\n", parametros[0]);
}
