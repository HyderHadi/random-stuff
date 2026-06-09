#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

#define DELETED -1
#define OCCUPIED 1
#define EMPTY 0

struct hashTable;
struct Entry *__FIND(struct hashTable *self, const char *key);
float __LOAD_FACTOR(struct hashTable *self);
struct hashTable *createTable();
void __RE_HASHER(struct hashTable *self);





// private methods

// 

unsigned int __GET_BUCKET(const char *key, int buckets) {

	unsigned int hash = 0;

	unsigned int bucket;

	for(int i = 0; key[i] != '\0'; i++) {
		hash = hash * 31 + key[i];
	}

	bucket = hash % buckets;

	return bucket;
}

void __INSERT (struct hashTable *self, const char *key, int value) {

	if(__LOAD_FACTOR(self) >= 0.75 || self->__tombs > self->__count) {
		__RE_HASHER(self);
		self->__tombs = 0;
	}

	struct Entry *found = __FIND(self, key);

	if(found != NULL) {
		found->__value = value;
		return;
	}

	unsigned int bucket = __GET_BUCKET(key, self->__buckets);
	int iterations = 0;
	while(iterations < self->__buckets) {
		if(self->__items[bucket].__state == EMPTY || self->__items[bucket].__state == DELETED) {
			self->__items[bucket].__value = value;
			self->__items[bucket].__key = malloc(strlen(key) + 1);
			strcpy(self->__items[bucket].__key, key);
			self->__items[bucket].__state = OCCUPIED;
			self->__count++;
			return;
		}
		else {
			bucket++;
			if(bucket >= self->__buckets) {
				bucket = 0;
			}
		}
		iterations++;
	};

	printf("INSERTION FAILED\n");
	return;
}

struct Entry *__FIND(struct hashTable *self, const char *key) {

	unsigned int bucket = __GET_BUCKET(key, self->__buckets);

	int iterations = 0;
	while(iterations < self->__buckets) {
		if(self->__items[bucket].__state == EMPTY) break;
		if(self->__items[bucket].__state != DELETED) {
			if(strcmp(self->__items[bucket].__key, key) == 0) {
				return &self->__items[bucket];
			}
		}

		bucket = (bucket + 1) % self->__buckets;
		iterations++;
	}

	return NULL;
}

void __DUMP (struct hashTable *self) {
	for(int i = 0; i < self->__buckets; i++) {
		printf("|Slot: (%d), State: (%d), Key: (%s), Value: (%d)|\n", i, self->__items[i].__state, self->__items[i].__key, self->__items[i].__value);
	}
}

void __DESTRUCTOR(struct hashTable *self) {

	int iterations = 0;
	while(iterations < self->__buckets) {
		if(self->__items[iterations].__key != NULL) {
			free(self->__items[iterations].__key);
			self->__items[iterations].__key = NULL;
		}
		iterations++;
	}

	free(self->__items);
	self->__items = NULL;

	free(self);
}

void __DELETE(struct hashTable *self, const char *key) {

	struct Entry *found = __FIND(self, key);

	if(!found) {
		printf("DOESNT EXIST!\n");
		return;
	}

	found->__state = DELETED;
	found->__value = 0;
	self->__count--;
	self->__tombs++;
	free(found->__key);
	found->__key = NULL;
}

float __LOAD_FACTOR(struct hashTable *self) {

	float retval = (float)self->__count / self->__buckets;

	return retval;
}


void __RE_HASHER(struct hashTable *self) {

	struct Entry *old_items = self->__items;
	int old_buckets = self->__buckets;

	if(self->__tombs > self->__count) {
		self->__items = calloc(self->__buckets, sizeof(struct Entry));
		self->__count = 0;
		for (int i = 0; i < old_buckets; i++) {
			if (old_items[i].__state == OCCUPIED) {
				__INSERT(self,
				         old_items[i].__key,
				         old_items[i].__value);

				free(old_items[i].__key);
			}
		}
		free(old_items);
		return;
	}

	self->__items = calloc(old_buckets * 2, sizeof(struct Entry));
	self->__buckets = old_buckets * 2;
	self->__count = 0;

	for (int i = 0; i < old_buckets; i++) {
		if (old_items[i].__state == OCCUPIED) {
			__INSERT(self,
			         old_items[i].__key,
			         old_items[i].__value);

			free(old_items[i].__key);
		}
	}

	free(old_items);
}




// Public method(s)

struct hashTable *createTable() {

	struct hashTable *t = malloc(sizeof(*t));

	t->__count = 0;
	t->__buckets = 2;
	t->__tombs = 0;
	t->__items = calloc(t->__buckets, sizeof(struct Entry));
	t->insert = &__INSERT;
	t->dump = &__DUMP;
	t->find = &__FIND;
	t->destructor = &__DESTRUCTOR;
	t->pop = &__DELETE;
	t->factor = &__LOAD_FACTOR;

	return t;
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
	if(buffer[0] == '\n') {
		return NULL;;
	}

	char *result = NULL;
	result = malloc(strlen(buffer) + 1);

	strcpy(result, buffer);

	result[strcspn(result, "\n")] = '\0';

	return result;
}