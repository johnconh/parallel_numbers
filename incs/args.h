#ifndef ARGS_H
#define ARGS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{
    MODE_HELP,
    MODE_FILE,
    MODE_ERROR
}ProgramMode;

typedef struct{
    ProgramMode mode;
    char *filename;
}ProgramArgs;

// Procesa los argumentos de la línea de comandos
// Devuelve una estructura ProgramArgs con los argumentos procesados
ProgramArgs* parseArgs(int argc, char* argv[]);

// Muestra la ayuda del programa
void showHelp(const char* programMode, ProgramMode mode);
void freeArgs(ProgramArgs* args);
#endif