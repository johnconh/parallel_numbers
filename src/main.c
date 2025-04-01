#include <stdio.h>
#include "../incs/args.h"
#include "../incs/config.h"

int main (int argc, char *argv[]) {

    ProgramArgs* args;
    Config config;

    args = parseArgs(argc, argv);

    if(args->mode == MODE_ERROR){
        showHelp(argv[0], MODE_ERROR);
        return 0;
    } else if(args->mode == MODE_HELP){
        showHelp(argv[0], MODE_HELP);
        return 1;
    }
    if (!readConfig(&config, args->filename)){
        freeArgs(args);
        return 1;
    }

    printf("Configuration loaded:\n");
    printf("-> Numbers per thread: %d\n", config.numbers_per_thread);
    printf("-> Number of threads:  %d\n", config.thread_num);

    freeArgs(args);
    return 0;
}