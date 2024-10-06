#include <stdio.h>
#include <stdlib.h>
#include "history.h"

List* init_history() {
  List* list = malloc(sizeof(List*));
  return list;
}

void add_history(List *list, char *str) {
  if(!list -> root) {
    list -> root = malloc(sizeof(Item *));
    list -> root -> id = 1;
    list -> root -> str = str;
    return;
  }

  int currId = 2;
  Item *temp = list -> root;
  while(temp -> next) {
    currId++;
    temp = temp -> next;
  }

  temp -> next = malloc(sizeof(Item *));
  temp -> next -> id = currId;
  temp -> next -> str = str;
  return;
}

char *get_history(List *list, int id) {
  Item *temp = list -> root;
  while(temp) {
    if(temp -> id == id) return temp -> str;
    temp = temp -> next;
  }
  
  return " ";
}

void print_history(List *list) {
  if(!list -> root) {
    printf("No elements!");
    return;
  }

  Item *temp = list -> root;
  while(temp) {
    printf("\n%d\t%s", temp -> id, temp -> str);
    temp = temp -> next;
  }

  return;
}
