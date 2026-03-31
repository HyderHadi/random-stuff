#include <stdio.h>

int main() { 

  printf("Multiplication table to 10x10\n");

  int multi_table[10][10];

  for(int i = 0;i < 10;i++) {
    for(int j = 0;j < 10;j++) {
      multi_table[i][j] = (j + 1) * (i + 1);
    }
  }

  for(int i = 1; i <= 10;i++) {
    for(int j = 1; j <= 10;j++) {
      printf("%d ", multi_table[i - 1][j - 1]);
      if ((j % 10) == 0) {
        printf("\n");
      }
    }
  }

  printf("\n");
  return 0;
  }
