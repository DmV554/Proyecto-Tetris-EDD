#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
     List * new = (List *)malloc(sizeof(List));
     assert(new != NULL);
     new->head = new->tail = new->current = NULL;
     return new;
}

void * firstList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return (void *)list->current->data;
}

void * nextList(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL; 
    list->current = list->current->next;
    return (void *)list->current->data;
}

void * lastList(List * list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->tail;
    return (void *)list->current->data;
}

void * prevList(List * list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return (void *)list->current->data;
}

void pushFront(List * list, const void * data) {
    assert(list != NULL);
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        new->next = new->prev = new;
        list->tail = new;
    } else {
        new->next = list->head;
        new->prev = list->tail;
        list->tail->next = new;
        list->head->prev = new;
    }
    
    list->head = new;
}

void pushBack(List * list, const void * data) {
    assert(list != NULL);
    
    Node * new = createNode(data);
    
    if (list->head == NULL) {
        new->next = new->prev = new;
        list->head = list->tail = new;
    } else {
        new->next = list->head;
        new->prev = list->tail;
        list->tail->next = new;
        list->head->prev = new;
        list->tail = new;
    }
}

void pushCurrent(List * list, const void * data) {
    assert(list != NULL && list->current != NULL);
    
    Node * new = createNode(data);
    Node * next = list->current->next;
    
    list->current->next = new;
    new->prev = list->current;
    
    if (next != NULL) {
        new->next = next;
        next->prev = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->tail = new;
    }
}

void * popFront(List * list) {
    assert(list != NULL && list->head != NULL);
    
    Node * node = list->head;
    void * data = (void *)node->data;
    
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->head = node->next;
        list->head->prev = list->tail;
        list->tail->next = list->head;
    }
    
    free(node);
    return data;
}

void * popBack(List * list) {
    assert(list != NULL && list->head != NULL);
    
    Node * node = list->tail;
    void * data = (void *)node->data;
    
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    } else {
        list->tail = node->prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
    
    free(node);
    return data;
}

void * popCurrent(List * list) {
    assert(list != NULL && list->current != NULL);
    
    Node * node = list->current;
    void * data = (void *)node->data;
    Node * prev = node->prev;
    Node * next = node->next;
    
    if (prev != NULL) {
        prev->next = next;
    } else {
        list->head = next;
        list->head->prev = list->tail;
        list->tail->next = list->head;
    }
    
    if (next != NULL) {
        next->prev = prev;
    } else {
        list->tail = prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
    
    free(node);
    return data;
}

void cleanList(List * list) {
    assert(list != NULL);
    
    while (list->head != NULL) {
        popFront(list);
    }
}

int sizeList(List * list) {
    if (list == NULL || list->head == NULL) {
        return 0;
    }
    
    int size = 0;
    Node * current = list->head;
    
    do {
        size++;
        current = current->next;
    } while (current != list->head);
    
    return size;
}

void* obtenerElementoPorPosicion(List* list, int position) {
    if (position < 0 || sizeList(list) == 0) {
        return NULL;  // Si la posición es inválida o la lista está vacía
    }
    
    list->current = list->head;
    int count = 0;

    while (count < position) {
        list->current = list->current->next;
        count++;

        if (list->current == list->head) {
            return NULL;  // Si se ha completado una vuelta completa en la lista sin encontrar la posición deseada
        }
    }

    return (void*)list->current->data;
}