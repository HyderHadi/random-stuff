#include <stdio.h>


// i made string_length equal to (-1) cause string indices start from number 0, probably there is a better way to represent what i want :(

char *reverse_string(char *string_input) {
    int string_length = -1;
    for (int i = 0;string_input[i] != '\0'; i++) {
        string_length += 1;
    }
    for (int i = 0;i <= string_length;i++) {
        char tmp = string_input[i];
        string_input[i] = string_input[string_length];
        string_input[string_length] = tmp;
        string_length--;
    }
    return string_input;
}

void check_palidnrome(char *string_input1, char *string_input2) {
  int string_length = -1;
  int flags = 0;
  for (int i = 0;string_input1[i] != '\0';i++) {
    string_length += 1;
  }
  for (int i = 0;i <= string_length;i++) {
    if (string_input1[i] == string_input2[string_length]) {
      flags = 1;
      string_length--;
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

  printf("Get me a word to see if it is a palindrome[Capital letters excluded XD]\n\n");
  char user_input[1000];
  while (scanf("%s", user_input) != EOF) {
    char *reversed = reverse_string(user_input);
    check_palidnrome(user_input, reversed); 
  }
  return 0;
}