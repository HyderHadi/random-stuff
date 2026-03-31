
#include <stdio.h>

void process(char *line) {

  // first function of the function;
  printf("\nString: %s\n", line);

  // second function of the function
  int count = 0;
  while (line[count] != '\0') {
    count++;
  }
  printf("Count=%d\n", count);

  // third function of the function
  if (count > 10) {
    printf("The tenth character is: %c", line[9]);
  }

  // fourth function of the function

  count = 0;
  while (line[count] != '\0') {
    if (line[count] == ' ') {
      line[count] = '-';
    }
    count++;
  }

  // fifth fucntion of the function
  printf("\nString: %s\n", line);
}

int main() {

  char input[1000];

  fgets(input, sizeof(input) - 1, stdin);

  process(input);

  return 0;
}