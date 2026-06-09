#ifndef HASHM_H
#define HASHM_H

struct hashTable {
	int __count;
	int __buckets;
	struct Entry *__items;
	int __tombs;

	// public methods

	void (*insert)(struct hashTable *self, const char *key, int value);
	void (*dump)(struct hashTable *self);
	struct Entry *(*find)(struct hashTable *self, const char *key);
	void (*destructor)(struct hashTable *self);
	void (*pop)(struct hashTable *self, const char *key);
	float (*factor)(struct hashTable *self);
};

struct Entry {
	int __value;
	char *__key;
	int __state;
};

char *read_line();
int intger_input();
struct hashTable *createTable();

#endif