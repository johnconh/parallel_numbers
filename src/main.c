#include <stdio.h>
#include <time.h>
#include "../incs/args.h"
#include "../incs/thread.h"

int main (int argc, char *argv[]) {

    ProgramArgs* args;
    Config config;
    List even_list, old_list;

    args = parseArgs(argc, argv);

    if(args->mode == MODE_ERROR){
        showHelp(argv[0], MODE_ERROR);
        freeArgs(args);
        return 1;
    } else if(args->mode == MODE_HELP){
        showHelp(argv[0], MODE_HELP);
        freeArgs(args);
        return 0;
    }
    if (!readConfig(&config, args->filename)){
        freeArgs(args);
        return 1;
    }

    printf("Configuration loaded:\n");
    printf("-> Numbers per thread: %d\n", config.numbers_per_thread);
    printf("-> Number of threads:  %d\n\n", config.thread_num);

    initList(&even_list);
    initList(&old_list);

    srand(time(NULL)); // Semilla para el generador de números aleatorios

    if(!run_threads(&config, &even_list, &old_list)){
        destroyList(&even_list);
        destroyList(&old_list);
        freeArgs(args);
        return 1;
    }

    merge_sort(&even_list);
    merge_sort(&old_list);
    // Imprimir listas
    listPrint(&even_list, "Even numbers");
    listPrint(&old_list, "Odd numbers");
    
    destroyList(&even_list);
    destroyList(&old_list);
    freeArgs(args);
    return 0;
}