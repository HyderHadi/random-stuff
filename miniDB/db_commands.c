#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0
#define EXIT -1

void parse(char *input, char *tokens[], int max_tokens) {

  int i = 0;

  char *token = strtok(input, " ");

  while (token != NULL && i < max_tokens) {

    tokens[i] = token;

    i++;

    token = strtok(NULL, " ");
  }
}

int db_commands(struct hashTable *self, FILE *fh, char *fileName) {

  printf("db> ");

  char *input = read_line();
  if (!input) {
    return FAILED;
  }

  char *tokens[3];

  parse(input, tokens, 3);

  char *endptr;

  int value = strtol(tokens[2], &endptr, 10);

  if (strcmp(tokens[0], "INSERT") == 0) {

    if (*endptr != '\0')
      return FAILED;

    self->insert(self, tokens[1], value);
    return SUCCESS;
  } else if (strcmp(tokens[0], "EXIT") == 0) {
    printf("BYE\n");
    return EXIT;
  } else if (strcmp(tokens[0], "GET") == 0) {
    struct Entry *cur = self->find(self, tokens[1]);
    if (cur) {
      printf("%d\n", cur->__value);
      return SUCCESS;
    }
    return FAILED;
  } else if (strcmp(tokens[0], "DELETE") == 0) {
    self->pop(self, tokens[1]);
  } else if (strcmp(tokens[0], "SAVE") == 0) {
    fh = fopen(fileName, "w");

    int iteratorCount = 0;

    while (iteratorCount < self->__buckets) {
        if (self->__items[iteratorCount].__key == NULL) {
            iteratorCount++;
            continue;
        }
      fprintf(fh, "%s %d\n", self->__items[iteratorCount].__key, self->__items[iteratorCount].__value);
      iteratorCount++;
    }

    fclose(fh);
    return SUCCESS;
  } else if (strcmp(tokens[0], "LOAD") == 0) {
    tokens[1] = fileName;
    fh = fopen(tokens[1], "r");

    char key[100];
    int val;
    while (fscanf(fh, "%s %d\n", key, &val) == 2) {
      self->insert(self, key, val);
    }
    fclose(fh);
    return SUCCESS;
  } else if (strcmp(tokens[0], "HELP") == 0) {
    printf("INSERT <key> <value>\nDELETE <key>\nGET <key>\nSAVE\nLOAD <filename>\nEXIT\nDUMPTBL\n");
    return SUCCESS;
  }
  else if(strcmp(tokens[0], "DUMPTBL") == 0) {
    self->dump(self);
  }
  return FAILED;
}