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
    bool number_found = false;
    bool threads_found = false;

    extension = strrchr(path, '.');
    if(extension == NULL || strcmp(extension, ".txt") != 0)
    {
        fprintf(stderr, "Error: configuration file must have .txt extension\n");
        return 0;
    }

    file = fopen(path, "r");
    if(file == NULL)
    {
        fprintf(stderr, "Error: could not open file %s\n", path);
        return 0;
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
            return 0;
        }

        *separator = '\0';
        strcpy(key, line);
        strcpy(value, separator + 2);

        trim(key);
        trim(value);

        if(strcmp(key, "numbers_per_thread") == 0)
        {
            config->numbers_per_thread = atoi(value);
            if( config->numbers_per_thread <= 0)
            {
                fprintf(stderr, "Error: invalid value for numbers_per_thread: %s\n", value);
                fclose(file);
                return 0;
            }
            number_found = true;
        } else if (strcmp(key, "thread_num") == 0)
        {
            config->thread_num = atoi(value);
            if( config->thread_num <= 0)
            {
                fprintf(stderr, "Error: invalid value for thread_numb: %s\n", value);
                fclose(file);
                return 0;
            }
            threads_found = true;
        } else
        {
            fprintf(stderr, "Error: invalid key in configuration file: %s\n", key);
            fclose(file);
            return 0;
        }

    }

    fclose(file);

    if (!number_found || !threads_found)
    {
        fprintf(stderr, "Error: numbers_per_thread not found in configuration file\n");
        return 0;
    }

    return 1;
}