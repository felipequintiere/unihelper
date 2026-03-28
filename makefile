CC := cc
CPPFLAGS := -DDEBUG=1 -I./include 
CFLAGS := -Wall -Wextra -Werror -O0
#CFLAGS := -O2

BINARY := a.out

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

.PHONY : clean
clean : ; rm -f $(OBJECTS)

.PHONY : run
run : $(BINARY)
	@./$(BINARY)
