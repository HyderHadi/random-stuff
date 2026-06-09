#ifndef DB_COMMANDS_H
#define DB_COMMANDS_H

#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

void parse(char *input, char *tokens[], int max_tokens);
int db_commands(struct hashTable *self, FILE *fh, char *fileName);

#endif