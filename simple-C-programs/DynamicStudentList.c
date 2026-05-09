#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* Objectives:  
    1- Make a bare functional list (Doubly linked list)
    2- add the sort and the highest functions afterward
    3- add more features if things are going ok
    4- Care about Encapulation and Abstraction ideas ...
*/
struct Student {
  char *__name;
  int __mark;
  int __age;
  struct Student *__next;
  struct Student *__prev;


  // Public Methods 
  char *(*name) (struct Student *self);
  int (*mark) (struct Student *self);
  int (*age) (struct Student *self);
};

struct StudentList {
  struct Student *__head;
  struct Student *__tail;
  int __count;

  // Methods (public)
  struct Student *(*highest) (struct StudentList *self);
  struct StudentList *(*sort) (struct StudentList *self);
  void (*put_student) (struct StudentList *self, char *name, int age, int mark);
  int (*size) (struct StudentList *self);
  void (*dump) (struct StudentList *self);
  struct Student *(*find) (struct StudentList *self, char *name);
  void (*destructor) (struct StudentList *self);
};

// Private Functions

struct Student *__FIND (struct StudentList *self, char *name) {

  struct Student *current = NULL;


  for(current = self->__head; current != NULL; current = current->__next) {
    if(strcmp(name, current->__name) == 0) {
      return current;
    }
  }
  return NULL;
}

void __PUT (struct StudentList *self, char *name, int age, int mark) {
  
  struct Student *old, *new;

  if (name == NULL) return;

  old = __FIND(self, name);

  if(old != NULL) {
    old->__age = age;
    old->__mark = mark;
    return;
  }

  new = malloc(sizeof(*new));

  new->__age = age;
  new->__mark = mark;

  new->__name = malloc(strlen(name) + 1);
  strcpy(new->__name, name);

  if(self->__head == NULL) {
    self->__head = new;
    self->__tail = new;
    new->__next = NULL;
    new->__prev = NULL;
    self->__count++;
    return;
  }

  self->__tail->__next = new;
  new->__prev = self->__tail;
  new->__next = NULL;
  self->__tail = new;

  self->__count++;
}

int __SIZE (struct StudentList *self) {

  return self->__count;
}

void __DUMP (struct StudentList *self) {

  struct Student *current;

  for(current = self->__head; current != NULL;current = current->__next) {

    printf("Name: %s\nAge: %d\nMark: %d\n", current->__name, current->__age, current->__mark);
  }
}

void __Destructor (struct StudentList *self) {

  struct Student *current, *tmp;

  current = self->__head;

  while(current) {
    free(current->__name);
    tmp = current->__next;
    free(current);
    current = tmp;
  }

  free(self);
}

char *__NAME (struct Student *self) {
  return self->__name;
}

int __AGE (struct Student *self) {
  return self->__age;
}

int __MARK (struct Student *self) {
  return self->__mark;
}





// The CONSTRUCTOR (Public)

struct StudentList *STUDENTLIST() {

  struct StudentList *S = malloc(sizeof(*S));

  S->__head = NULL;
  S->__tail = NULL;
  S->__count = 0;

  // Methods 
  S->put_student = &__PUT;
  S->size = &__SIZE;
  S->dump = &__DUMP;
  S->find = &__FIND;
  S->destructor = &__Destructor;

  return S;
}


int main() {

  
  
  return 0;
}