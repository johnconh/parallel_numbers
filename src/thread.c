
#include "../incs/thread.h"

void thread_data_init(ThreadData* data, int numbers_per_thread, int thread_id, List* even_list, List* odd_list){
    data->numbers_per_thread = numbers_per_thread;
    data->thread_id= thread_id;
    data->even_list = even_list;
    data->odd_list = odd_list;
}

int generate_unique_number(List* even_list, List* odd_list){
    int number;
    int max_tries = 1000; // Evito bucles infinitos
    do{
        number = rand() % 10000;
        max_tries--;
        //Si hemos generado muchos números y no hemos encontrado uno único, generamos uno aleatorio
        if (max_tries <= 0){ 
            number = rand() % 10000;
            break;
        }
    } while (listContains(even_list, number) || listContains(odd_list, number));
    return number;
}

void* thread_function(void* arg){
    ThreadData* data = (ThreadData*)arg;
    int count = 0;

    srand(time(NULL) ^ (data->thread_id * 1000)); // Semilla para el generador de números aleatorios

    printf("Thread %d: Generating %d numbers...\n", data->thread_id, data->numbers_per_thread);

    while( count < data->numbers_per_thread){
        int number = generate_unique_number(data->even_list, data->odd_list);
        if (number % 2 == 0){
            listAdd(data->even_list, number);
        } else {
            listAdd(data->odd_list, number);
        }
        //printf("Thread %d: Generated number %d\n", data->thread_id, number);
        count++;
        usleep(1000); 
    }
    printf("Thread %d: Generated %d numbers\n", data->thread_id, count);

    return NULL;
}

int run_threads(Config* config, List* even_list, List* odd_list){
    pthread_t* threads;
    ThreadData* thread_data;
    int i;

    // Asignar memoria para los threads y los datos de los threads
    threads = (pthread_t*)malloc(sizeof(pthread_t) * config->thread_num);
    if (!threads){
        fprintf(stderr, "Error run_threads: Memory allocation error\n");
        return 0;
    }
    thread_data = (ThreadData*)malloc(sizeof(ThreadData) * config->thread_num);
    if (!thread_data){
        fprintf(stderr, "Error run_threads: Memory allocation error\n");
        free(threads);
        return 0;
    }

    for (i = 0; i < config->thread_num; i++){
        thread_data_init(&thread_data[i], config->numbers_per_thread, i, even_list, odd_list);
        if (pthread_create(&threads[i], NULL, thread_function, &thread_data[i])){
            fprintf(stderr, "Error run_threads: pthread_create error\n");

            // Esperar a que los threads anteriores terminen
            for (int j = 0; j < i; j++){ 
                pthread_join(threads[j], NULL);
            }
            free(threads);
            free(thread_data);
            return 0;
        }
    }
    for (i = 0; i < config->thread_num; i++){
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(thread_data);
    return 1;
}