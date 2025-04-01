#include "../incs/list.h"

void initList(List* list){
    list->head = NULL;
    pthread_mutex_init(&list->mutex, NULL);
}

void destroyList(List* list){
    Node* current = list->head;
    Node* next;
    while(current){
        next = current->next;
        free(current);
        current = next;
    }

    pthread_mutex_destroy(&list->mutex);
}

int listContains(List* list, int data){
    pthread_mutex_lock(&list->mutex);
    Node* current = list->head;
    while(current){
        if(current->data == data){
            pthread_mutex_unlock(&list->mutex);
            return 1;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&list->mutex);
    return 0;
}

int listAdd(List* list, int data){

    if(listContains(list, data)){
        return 0;
    }

    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node){
        fprintf(stderr, "Error listAdd: Memory allocation error\n");
        return 0;
    }

    new_node->data = data;
    pthread_mutex_lock(&list->mutex);
    new_node->next = list->head;
    list->head = new_node;
    pthread_mutex_unlock(&list->mutex);
    return 1;
}

void listPrint(List* list, const char* name){
    pthread_mutex_lock(&list->mutex);

    printf("\nList: %s\n", name);

    int pos = 1;
    Node* current = list->head;

    if (!current){
        printf("Empty list\n");
    }
    while(current){
        printf("Position %d: %d \n",pos, current->data);
        current = current->next;
        pos++;
    }
    pthread_mutex_unlock(&list->mutex);
}