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
  List *lista = (List*) malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  return lista;
}

void * firstList(List * list) {
  if(list->head && list->head->data){
    list->current=list->head; 
  }
  return (void *)list->current->data;
}

void * nextList(List * list) {
  if(list->current == NULL) return NULL; 
  if(list->current->next == NULL) return NULL;
  list->current = list->current->next; 
  return (void *)list->current->data; 
}

void * lastList(List * list) {
  if(list->tail && list->tail->data){
    list->current =list->tail; 
  }
  return (void *)list->current->data;
}

void * prevList(List * list) {
  if(list->current == NULL) return NULL; 
  if(list->current->prev == NULL) return NULL;
  list->current = list->current->prev; 
  return (void *)list->current->data; 
}

void pushFront(List * list, const void * data) {
  Node* n = createNode(data);

  n->next = list->head;
  if(list->head != NULL) list->head->prev = n;
  list->tail = n;
  list->head = n;
  n->prev=NULL;
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node *n = createNode(data);
  if(list->current != NULL)
  list->current->next = n;
  n->prev = list->current;
  list->tail=n; 
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node* n = list->current;
    const void *x = list->current->data;

    // if (data == NULL) return NULL;

    if(n->prev != NULL){
      n->prev->next=n->next;
    }else{
      list->head = n->next;
    }

    if(n->next != NULL)
    n->next->prev=n->prev;

   list->tail = list->tail->prev;
   list->tail->next=NULL;
    
    list->current = n;
   
   free(n);
    return (void* )x;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
  }
}