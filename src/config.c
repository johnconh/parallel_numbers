#include "../incs/config.h"

void trim (char* s)
{
    char *start = s;
    char *end;

    if(s == NULL) // Si es NULL, no hacemos nada
    {
        return;
    }

    while(isspace(*start)) // Mientras el primer caracter sea un espacio, avanzamos
    {
        start++;
    }

    if(*start == 0) // Si llegamos al final, devolvemos la cadena vacía
    {   
        *s = '\0';
        return;
    }


    end = start + strlen(start) - 1;
    while(end > start && isspace(*end)) // Mientras el último caracter sea un espacio, retrocedemos
    {
        end--;
    }

    *(end + 1) = '\0';

    if(start != s)
    {
        memmove(s, start, (end - start) + 2); // Movemos la cadena para que empiece en s
    }
}

int readConfig(Config *config, const char *path)
{
    FILE *file;
    char line[256];
    char *extension;
    // int number_found = 0;
    // int threads_found = 0;
    printf("path: %s\n", path);

    extension = strrchr(path, '.');
    if(extension == NULL || strcmp(extension, ".txt") != 0)
    {
        fprintf(stderr, "Error: configuration file must have .txt extension");
        return 1;
    }

    file = fopen(path, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error: could not open file %s\n", path);
        return 1;
    }

    while (fgets(line, sizeof(line), file))
    {
        char key[256], value[256];
        char *separator;

        char* newline = strchr(line, '\n');
        if(newline)
        {
            *newline = '\0';
        }

        if(line[0] == '\0')
        {
            continue;
        }

        separator = strchr(line, '=');
        if(separator == NULL)
        {
            fprintf(stderr, "Error: invalid line in configuration file: %s\n", line);
            return 1;
        }

        *separator = '\0';
        strcpy(key, line);
        strcpy(value, separator + 2);

        trim(key);
        trim(value);

    }

    fclose(file);
    return 0;
}