#include <stdio.h>

int main() {
  char token[256];
  int position = 0, value, length;
  char memory[256] = {0};

  while (scanf("%s", token) == 1) {

    if (token[0] == 'q') {
      break;
    }

    for (length = 0; token[length] != '\0'; length++)
      ;

    if (length > 1) {
      value = 0;
      for (int i = 0; token[i] != '\0'; i++) {
        if (length == 3) {
          int tmp = token[i];
          tmp = tmp - '0';
          tmp = tmp * 100;
          value += tmp;
          length--;
        } else if (length == 2) {
          int tmp = token[i];
          tmp = tmp - '0';
          tmp = tmp * 10;
          value += tmp;
          length--;
        } else if (length == 1) {
          int tmp = token[i];
          tmp = tmp - '0';
          value += tmp;
          length--;
          memory[position] = value;
        }
      }
    } else if (token[0] == '>') {
      position++;
    } else if (token[0] == '<') {
      position--;
    }
  }
  printf("Memory:\n%s\n", memory);
}