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
    readConfig(&config, args->filename);
    freeArgs(args);
    return 0;
}