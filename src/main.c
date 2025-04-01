#include <stdio.h>
#include "../incs/args.h"

int main (int argc, char *argv[]) {

    ProgramArgs args;

    args = parseArgs(argc, argv);

    if(args.mode == MODE_ERROR){
        showHelp(argv[0], MODE_ERROR);
        return 0;
    } else if(args.mode == MODE_HELP){
        showHelp(argv[0], MODE_HELP);
        return 1;
    }

    if (args.filename != NULL) {
        printf("entrando al if\n");
        free(args.filename);
    }

    return 0;
}