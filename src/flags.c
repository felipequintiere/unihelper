#include <stdio.h>
#include "../include/flags.h"

void flag_help(const char * const nome_do_programa)
{
    fprintf(stderr,
		"Usage: %s [OPTION]... [FILE]...\n\n"
		"  -f, --file <FILE>        path to data file\n"
		"  -v, --version     output version information and exit\n"
		"  -h, --help        display this help and exit\n",
		nome_do_programa
	);
}

void flag_version(const char * const nome_do_programa)
{
	fprintf(stderr,
		"%s (c) 2026 %s, Inc.\n"
		"Compiled on %s at %s\n",
		nome_do_programa,nome_do_programa,
 		__DATE__, __TIME__
	);
}

void flag_invalid(char * const *parametros)
{
	// passando o nome do programa e a primeira flag
	fprintf(stderr,
		"%s: invalid option -- '%s'\n"
		"Try '%s --help' for more information.\n",
		parametros[0], parametros[1],  // nome e primeira flag 
		parametros[0]
	);
}
