#include <stdio.h>
#include <string.h>



void reverse(char *destination, char *source) {
  int length = strlen(source);
  int i;
  for(i = 0;source[i] != '\0';i++) {
    destination[i] = source[length - 1];
    length--;
  }
  destination[i] = '\0';
}

void palindrom(char *input) {

  char tmp_dest[100];

  reverse(tmp_dest , input);

  for(int i = 0;input[i] != '\0';i++) {
    if(input[i] != tmp_dest[i]) {
      printf("Not a palindrome\n");
      return;
    }
  }
  printf("the word is a palindrome\n");

}

int main() {

  char source[100];
  char destination[100];

  fgets(source, sizeof(source), stdin);

  // to lowerCase the input letters
  for(int i = 0;source[i] != '\0';i++) {
    if(source[i] >= 'A' && source[i] <= 'Z') {
      source[i] += 32;
    }
  }

  source[strcspn(source, "\n")] = '\0';
  palindrom(source);
  return 0;
}