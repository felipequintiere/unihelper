
// ANSI color escape sequences
#define RESET       "\033[0m" 
#define BLACK       "\033[0;90m" 
#define RED         "\033[0;91m" 
#define GREEN       "\033[0;92m" 
#define BROWN       "\033[0;93m" 
#define BLUE        "\033[0;94m" 
#define PURPLE      "\033[0;95m" 
#define CYAN        "\033[0;96m" 
#define LIGHT_GRAY  "\033[0;97m" 

// nota: o macro DEBUG é definido no makefile
#if defined(DEBUG) && DEBUG==1
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, RED"\n [DEBUG] %s:%d: "RESET \
				fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif
