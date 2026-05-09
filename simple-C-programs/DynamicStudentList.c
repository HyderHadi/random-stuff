#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student {
  char *__name;
  int __mark;
  int __age;
  struct Student *__next;
  struct Student *__prev;
};

struct StudentList {
  struct Student *__head;
  struct Student *__tail;
  int __count;

  // Methods
  struct Student *(*highest) (struct StudentList self);
  struct StudentList *(*sort) (struct StudentList self);
  void (*put_student) (struct StudentList self, char *name, int age, int mark);
  int (*size) (struct StudentList self);
  void (*dump) (struct StudentList self);
  struct Student *(*find) (struct StudentList self, char *name);
  void (*destructor) (struct StudentList self);
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

  old = __FIND(self, name);

  if(old != NULL) {
    old->__age = age;
    old->__mark = mark;
    return;
  }


}




int main() {

  
  
  return 0;
}