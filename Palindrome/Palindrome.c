#include <stdio.h>

char *reverse(char *input) {
    int len = -1;
    for (int i = 0;input[i] != '\0'; i++) {
        len += 1;
    }
    for (int i = 0;i <= len;i++) {
        char tmp = input[i];
        input[i] = input[len];
        input[len] = tmp;
        len--;
    }
    return input;
}

void compareString(char *input1, char *input2) {
  int len = -1;
  int flags = 0;
  for (int i = 0;input1[i] != '\0';i++) {
    len += 1;
  }
  for (int i = 0;i <= len;i++) {
    if (input1[i] == input2[len]) {
      flags = 1;
      len--;
    }
    else {
      flags = 0;
      printf("Not a palindrome\n\n");
      break;
    }
  }
  if (!flags == 0) {
    printf("This is a palindrome\n\n");
  }
}


int main()
{

  printf("Get me a word to see if it is a palindrome\n\n");
  char inp[1000];
  while (scanf("%s", inp) != EOF) {
    char *tmp = reverse(inp);
    compareString(inp, tmp); 
  }
  return 0;
}