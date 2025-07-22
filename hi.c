# include <stdio.h>
# include <stdlib.h>

// REUSABLE INTEGER ARRAY IN CASE YOU NEED AN INTEGER ARRAY
typedef struct {
    int *data;
    int size;
    int capacity;
} IntArray;

void initArray(IntArray *arr, int initialCapacity) {
    arr->data = malloc(initialCapacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initialCapacity;
}

void append(IntArray *arr, int value) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(int));
        if (arr->data == NULL) {
            printf("Reallocate failed!!\n");
            exit(1);
        } 
    }

    arr->data[arr->size] = value;
    arr->size++;
}

int main () {
    int x = 5;
    int y = x++;
    printf("%d\n", y);
    y = ++x;
    printf("%d\n\n", y);


    return 0;
}