#include "../incs/args.h"

ProgramArgs parseArgs(int argc, char* argv[]){
    ProgramArgs args;
    args.mode = MODE_ERROR;
    args.filename = NULL;

    if(argc < 2){
        fprintf(stderr, "Error: No arguments\n");
        return args;
    }

    if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
        args.mode = MODE_HELP;
        return args;
    } else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0){
        if(argc < 3){
            fprintf(stderr, "Error: No filename\n");
            return args;
        }

        args.mode = MODE_FILE;
        args.filename =(char *)malloc(strlen(argv[2]) + 1);
        if(!args.filename){
            fprintf(stderr, "Error args.filename: Memory allocation error\n");
            return args;
        }
        return args;
    }
    fprintf(stderr, "Error: Invalid argument: %s\n", argv[1]);
    return args;
}

void showHelp(const char* programName, ProgramMode mode){

    if(mode == MODE_ERROR){
        printf("Usage: %s [OPTION] \n", programName);
        printf("Options:\n");
        printf("  -h, --help\t\tShow this help\n");
        printf("  -f, --file FILE\tSpecify the file to process\n");
    }else if (mode == MODE_HELP){
        printf("Usage: %s [OPTION] \n", programName);
        printf("Example: %s -f file.txt\n", programName);
    }
}