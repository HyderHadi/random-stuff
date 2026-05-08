#include <stdio.h>
#include <stdlib.h>

struct Student {
  char *__name;
  int __age;
  int __mark;
  struct Student *__next;
};

struct StudentList {
  struct Student *__head;
  struct Student *__tail;
  int __count;

  // Methods;

  int (*highest) (struct StudentList *self);
  void (*sort) (struct StudentList *self);
};


int Highest_mark (struct StudentList *self) {
  int def = 0;
  int res;
  struct Student *tmp = NULL;

  if(self->__head != NULL) {
    for(tmp = self->__head; self->__count > 0; tmp = tmp->__next) {
      if(tmp->__mark > tmp->__next->__mark) {
        res = tmp->__mark;
      }
    }
    return res;
  }

  return def;
}

void Sort_by_mark(struct StudentList *self) {
  
}


int main() {

  return 0;
}