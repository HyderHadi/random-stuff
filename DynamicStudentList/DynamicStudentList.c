#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StudentList *STUDENTLIST();

/* Objectives:
    1- Make a bare functional list (Doubly linked list)
    2- add the sort and the highest functions afterward
    3- add more features if things are going ok
    4- Care about Encapsulation and Abstraction ideas ...
*/
struct Student {
  char *__name;
  int __mark;
  int __age;
  struct Student *__next;
  struct Student *__prev;

  // Public Methods
  char *(*name)(struct Student *self);
  int (*mark)(struct Student *self);
  int (*age)(struct Student *self);
};

struct StudentList {
  struct Student *__head;
  struct Student *__tail;
  int __count;

  // Methods (public)
  struct Student *(*highest)(struct StudentList *self);
  struct StudentList *(*sort)(struct StudentList *self);
  void (*put_student)(struct StudentList *self, char *name, int age, int mark);
  int (*size)(struct StudentList *self);
  void (*dump)(struct StudentList *self);
  struct Student *(*find)(struct StudentList *self, char *name);
  void (*destructor)(struct StudentList *self);
  void (*pop)(struct Student *self, struct StudentList *list);
};

// Private Functions

char *__NAME(struct Student *self) { return self->__name; }

int __AGE(struct Student *self) { return self->__age; }

int __MARK(struct Student *self) { return self->__mark; }

void __POP(struct Student *self, struct StudentList *list) {

  if (self == NULL || list == NULL)
    return;

  // if node is head
  if (self->__prev == NULL) {
    list->__head = self->__next;
  } else {
    self->__prev->__next = self->__next;
  }

  // if node is tail
  if (self->__next == NULL) {
    list->__tail = self->__prev;
  } else {
    self->__next->__prev = self->__prev;
  }

  list->__count--;

  free(self->__name);
  free(self);
}

struct Student *__FIND(struct StudentList *self, char *name) {

  struct Student *current = NULL;

  for (current = self->__head; current != NULL; current = current->__next) {
    if (strcmp(name, current->__name) == 0) {
      return current;
    }
  }
  return NULL;
}

void __PUT(struct StudentList *self, char *name, int age, int mark) {

  struct Student *old, *new;

  if (name == NULL)
    return;

  old = __FIND(self, name);

  if (old != NULL) {
    old->__age = age;
    old->__mark = mark;
    return;
  }

  new = malloc(sizeof(*new));

  new->__age = age;
  new->__mark = mark;

  new->__name = malloc(strlen(name) + 1);
  strcpy(new->__name, name);

  if (self->__head == NULL) {
    self->__head = new;
    self->__tail = new;
    new->__next = NULL;
    new->__prev = NULL;
    new->age = &__AGE;
    new->mark = &__MARK;
    new->name = &__NAME;
    self->__count++;
    return;
  }

  self->__tail->__next = new;
  new->__prev = self->__tail;
  new->__next = NULL;
  self->__tail = new;
  new->age = &__AGE;
  new->mark = &__MARK;
  new->name = &__NAME;

  self->__count++;
}

int __SIZE(struct StudentList *self) { return self->__count; }

void __DUMP(struct StudentList *self) {

  struct Student *current;

  for (current = self->__head; current != NULL; current = current->__next) {

    printf("Name: %s\nAge: %d\nMark: %d\n", current->__name, current->__age,
           current->__mark);
    printf("------------------------------\n");
  }
}

void __Destructor(struct StudentList *self) {

  struct Student *current, *tmp;

  current = self->__head;

  while (current) {
    free(current->__name);
    tmp = current->__next;
    free(current);
    current = tmp;
  }

  free(self);
}

struct Student *__HIGHEST(struct StudentList *self) {

  if (self == NULL || self->__head == NULL)
    return NULL;

  struct Student *current = self->__head;
  struct Student *highest = self->__head;

  while (current != NULL) {

    if (current->__mark > highest->__mark) {
      highest = current;
    }

    current = current->__next;
  }

  return highest;
}

struct StudentList *__SORT(struct StudentList *self) {

  struct StudentList *S = STUDENTLIST();

  while (self->__head != NULL) {

    struct Student *highest = __HIGHEST(self);

    if (highest == NULL)
      break;

    __PUT(S, highest->__name, highest->__age, highest->__mark);

    __POP(highest, self);
  }

  return S;
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
  S->highest = &__HIGHEST;
  S->sort = &__SORT;
  S->pop = &__POP;
  return S;
}

// input functions (Public)

int intger_input() {

  int tmp;

  while (1) {

    if ((scanf("%d", &tmp)) == 1) {
      while (getchar() != '\n')
        ;
      break;
    }

    while (getchar() != '\n')
      ;
    printf("Invalid input, try again: ");
  }

  return tmp;
}

char *read_line() {

  char buffer[1024];

  if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
    return NULL;
  }

  char *result = NULL;
  result = malloc(strlen(buffer) + 1);

  strcpy(result, buffer);

  result[strcspn(result, "\n")] = '\0';

  return result;
}

int main() {

  struct StudentList *list = STUDENTLIST();
  int op_code;
  char *name = NULL;
  int age = 0;
  int mark = 0;
  struct Student *tmp = NULL;

  printf("Welcome to DynamicStudentList, Enter 1 to show commands, to exit "
         "Enter 0\n");
  while ((op_code = intger_input()) != 0) {

    switch (op_code) {
    case 1:
      printf("-Enter a student [Enter no. 2]\n-Find a student [Enter "
             "no. 3]\n-Sort students [Enter no. 4]\n-Show student entries[Enter "
             "no. 5]\n-Find best student [Enter no. 6]\n-To exit [Enter no. 0]\n");
      break;
    case 2:
      printf("name -> Enter -> Age -> Enter -> Mark -> Enter\n");
      name = read_line();
      age = intger_input();
      mark = intger_input();

      list->put_student(list, name, age, mark);
      tmp = list->find(list, name);

      printf("Student's name: %s, Age: %d, Mark: %d\n", tmp->name(tmp),
             tmp->age(tmp), tmp->mark(tmp));
      free(name);
      age = 0;
      mark = 0;
      break;
    case 3:
      printf("Give a name of the student to search it up (CASE SENSITIVE): ");
      name = read_line();

      tmp = list->find(list, name);
      if (tmp == NULL) {
        printf("Doesn't Exist!\n");
      } else {
        printf("STUDENT FOUND!\n");
        printf("Student's name: %s, Age: %d, Mark: %d\n", tmp->name(tmp),
               tmp->age(tmp), tmp->mark(tmp));
      }
      free(name);
      break;
    case 4:
      if (list->size(list) == 0) {
        printf("No student available!, try a Entering some: ");
        break;
      }
      list = list->sort(list);
      if (list == NULL) {
        printf("No student available\n");
      } else {
        printf("SORTED:\n");
        list->dump(list);
      }
      break;

    case 5:
      if (list->size(list) == 0) {
        printf("No student available!, try a Entering some: ");
        break;
      }
      list->dump(list);
      break;

    case 6:
      if (list->size(list) == 0) {
        printf("No student available!, try a Entering some: ");
        break;
      }

      tmp = list->highest(list);
      printf("The best student is: %s, Age: %d, Mark: %d\n", tmp->name(tmp),
             tmp->age(tmp), tmp->mark(tmp));
      break;

    default:
      printf("Invalid command, try a command[1 for help]: ");
    }
  }

  list->destructor(list);

  return 0;
}