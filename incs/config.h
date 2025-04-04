#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    int numbers_per_thread;
    int thread_num;
} Config;

// Funcion que lee el archivo de configuracion
int readConfig(Config *config,  const char *path);

#endif