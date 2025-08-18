#include <stdio.h>

void selection_sort(int *Array, int length) {
  for (int i = 0;i < length;i++) {
    int current = Array[i];
    int smallest = Array[i];
    int tmp = i;
    for (int j = i + 1;j < length;j++) {
      if (Array[j] < smallest) {
        smallest = Array[j];
        tmp = j;
      }
    }
    Array[i] = smallest;
    Array[tmp] = current;
  }
}

int main() {

  int Array[] = {95, 12, 84, 23, 7, 66, 41, 59, 18, 32, 73, 5, 91, 46, 27, 63, 14, 39, 100, 2, 77, 50, 35, 9, 81, 3, 45, 22, 60, 88, 11, 36, 71, 25, 49, 16, 68, 1, 53, 29, 86, 19, 43, 30, 62, 8, 79, 4, 21, 98};
  int ArrayLength = sizeof(Array) / sizeof(Array[0]);
  printf("Not Sorted: ");
  for (int i = 0;i < ArrayLength;i++) {
    printf("%d ", Array[i]);
  }
  printf("\n\n");
  selection_sort(Array, ArrayLength);
  printf("Sorted: ");
  for (int i = 0;i < ArrayLength;i++) {
    printf("%d ", Array[i]);
  }
  printf("\n");
  return 0;
}