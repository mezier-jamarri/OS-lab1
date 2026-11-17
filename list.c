// list/list.c
// 
// Implementation for linked list.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist; // Added return statement
}

void list_free(list_t *l) {
  if (l == NULL) return;
  
  node_t *curr = l->head;
  node_t *next = NULL;
  
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  free(l);
}

void list_print(list_t *l) {
  node_t *curr = l->head;
  while (curr != NULL) {
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 10024);
  strcpy(buf, ""); // Initialize buffer to avoid junk data
  char tbuf[20];

  node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count; 
}

void list_add_to_back(list_t *l, elem value) {
  node_t *new_node = getNode(value);
  if (l->head == NULL) {
    l->head = new_node;
    return;
  }
  
  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = new_node;
}

void list_add_to_front(list_t *l, elem value) {
  node_t *cur_node = getNode(value);

  /* Insert to front */
  node_t *head = l->head;  // get head of list

  cur_node->next = head;
  l->head = cur_node;
}

node_t * getNode(elem value) {
  node_t *mynode;

  mynode = (node_t *) malloc(sizeof(node_t));
  mynode->value = value;
  mynode->next = NULL;

  return mynode;
}

void list_add_at_index(list_t *l, elem value, int index) {
  // Using 1-based indexing as specified in list.h
  if (index <= 1 || l->head == NULL) {
    list_add_to_front(l, value);
    return;
  }
  
  node_t *new_node = getNode(value);
  node_t *curr = l->head;
  int i = 1;
  
  while (curr->next != NULL && i < index - 1) {
    curr = curr->next;
    i++;
  }
  
  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) { 
  if (l->head == NULL) return -1;
  
  node_t *curr = l->head;
  node_t *prev = NULL;
  
  while (curr->next != NULL) {
    prev = curr;
    curr = curr->next;
  }
  
  elem val = curr->value;
  
  if (prev == NULL) { // Only one element in the list
    l->head = NULL;
  } else {
    prev->next = NULL;
  }
  
  free(curr);
  return val; 
}

elem list_remove_from_front(list_t *l) { 
  if (l->head == NULL) return -1;
  
  node_t *curr = l->head;
  elem val = curr->value;
  
  l->head = curr->next;
  free(curr);
  return val; 
}

elem list_remove_at_index(list_t *l, int index) { 
  if (l->head == NULL) return -1;
  
  // Using 1-based indexing
  if (index <= 1) {
    return list_remove_from_front(l);
  }
  
  node_t *curr = l->head;
  node_t *prev = NULL;
  int i = 1;
  
  while (curr != NULL && i < index) {
    prev = curr;
    curr = curr->next;
    i++;
  }
  
  if (curr == NULL) return -1; // Index out of bounds
  
  elem val = curr->value;
  prev->next = curr->next;
  free(curr);
  
  return val; 
}

bool list_is_in(list_t *l, elem value) { 
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false; 
}

elem list_get_elem_at(list_t *l, int index) { 
  node_t *curr = l->head;
  int i = 1;
  
  while (curr != NULL && i < index) {
    curr = curr->next;
    i++;
  }
  
  if (curr == NULL) return -1; // Out of bounds
  return curr->value; 
}

int list_get_index_of(list_t *l, elem value) { 
  node_t *curr = l->head;
  int i = 1;
  
  while (curr != NULL) {
    if (curr->value == value) return i;
    curr = curr->next;
    i++;
  }
  
  return -1; // Not found
}