#ifndef LIST_H
#define LIST_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    pthread_mutex_t mutex;
} List;

void initList(List* list);
void destroyList(List* list);
int listAdd(List* list, int data);
void listPrint(List* list, const char* name);
int listContains(List* list, int data);

#endif