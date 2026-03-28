########################################
# .makefile1

CC := cc
CFLAGS := -Wall -Wextra -Werror -O1
# note: you may use the -D flag:
#     CFLAGS := ... -DDEBUG

executable := a.out
objects := main.o src/flags.o

# FIRST METHOD:
#
#$(executable) : $(objects)
#	$(CC) $(CFLAGS) -o $(executable) $(objects)
#	#cc -o $(executable) $(objects)
#
#main.o : main.c include/types.h include/flags.h
#	$(CC) $(CFLAGS) -o main.o -c main.c
#flags.o : src/flags.c include/flags.h
#	$(CC) $(CFLAGS) -o flags.o -c src/flags.c

# SECOND METHOD
$(executable) : $(objects)
	$(CC) -o $(executable) $(objects)
#
main.o : ./include/types.h ./include/flags.h
src/flags.o : ./include/flags.h
#
#main.o : main.c include/types.h include/flags.h
#src/flags.o : src/flags.c ./include/flags.h
# note: I didn't define how '.o' files are built,
# make will try its built-in implict rules:
# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
# clean :
#	-rm $(executable) $(objects)
#
# one line and avoid the odd use of '-rm':
clean : ; rm -f $(executable) $(objects)

.PHONY : run
run : $(executable)
	./$(executable)



########################################
# .makefile2

CC := cc
OPT := -O0
INCDIRS := -I.
CFLAGS := -Wall -Wextra -Werror -DDEBUG=1 $(OPT) $(INCDIRS)
# note: '-DDEBUG' defines DEBUG macro as 1 by default in GCC

OBJECTS := main.o src/flags.o

BINARY = uni
all : $(BINARY)

$(BINARY) : $(OBJECTS)
	$(CC) -o $@ $^

%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $^
# IMPORTANT NOTE (implicit rules):
# if the header files included in the %.c
# are changed, make will not track these 
# modifications and, therefore, it will
# not recompile

.PHONY : clean
clean : ; rm -f $(BINARY) $(OBJECTS)

.PHONY : run
run : $(BINARY)
	@./$(BINARY)



########################################
# .makefile3

# note: in debian, cc (c compiler) is a link to gcc:
# $ type cc
# cc is /usr/bin/cc
# $
# $ ls /usr/bin/cc
# lrwxrwxrwx 1 root root 20 Oct 10  2024 /usr/bin/cc -> /etc/alternatives/cc*
# $
# $ ls /etc/alternatives/cc
# lrwxrwxrwx 1 root root 12 Oct 10  2024 /etc/alternatives/cc -> /usr/bin/gcc*



# compiler and linker
CC := cc

# preprocessor flags
CPPFLAGS := -DDEBUG=1 -I./include 
# note: '-DDEBUG' defines DEBUG macro as 1 by default in GCC
# note: '-I' tells the preprocessor to also search the given \
directories when resolving `#include` directives; one may write \
`#include "file.h"` instead of `#include "./include/file.h"` in \
the source files

# compiler flags for .c files
CFLAGS := -Wall -Wextra -Werror -O0

# note: CC, CPPFLAGS and CFLAGS flags are automatically used by built-in implicit rules



BINARY := a.out

#SOURCE_DIRS := . ./src/
#SOURCE_FILES := $(foreach DIR,$(SOURCE_DIRS),$(wildcard $(DIR)/*.c)
SOURCE_FILES := $(wildcard ./*.c ./src/*.c)
OBJECTS := $(patsubst %.c,%.o,$(SOURCE_FILES))
#DEPENDENCY_FILES := $(patsubst %.c,%.d,$(SOURCE_FILES))

# vpath directives
vpath %.h ./include/
vpath %.c ./src/

all : $(BINARY)

$(BINARY) : $(OBJECTS)
	$(CC) -o $@ $^

main.o : ./include/macros.h ./include/types.h ./include/flags.h
flags.o : ./include/flags.h
# note: make will find the respective .c file (prerequisite) of \
its target (.o file) through the vpath directive; it's using \
implicit rules - %.o:%.c - 


.PHONY : clean
clean : ; rm -f $(OBJECTS)

.PHONY : run
run : $(BINARY)
	@./$(BINARY)



########################################
