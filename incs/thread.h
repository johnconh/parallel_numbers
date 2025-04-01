#ifndef TRHEAD_H
#define TRHEAD_H

#include "list.h"
#include "config.h"
#include <time.h>
#include <unistd.h>

// Estructura para pasar datos a los hilos
typedef struct ThreadData {
    int thread_id;
    int numbers_per_thread;
    List* even_list;
    List* odd_list;
} ThreadData;


// Inicializa la estructura ThreadData
void thread_data_init(ThreadData* data, int numbers_per_thread, int thread_id, List* even_list, List* odd_list);

// Función que ejecuta cada hilo
void *thread_function(void* arg);

// Crea y ejecuta los hilos
int run_threads(Config* config, List* even_list, List* odd_list);

void merge_sort(List* list);

#endif