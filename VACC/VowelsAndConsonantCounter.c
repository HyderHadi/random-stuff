# include <stdio.h>

#define INCREMENT 1
#define TRUE 1
#define FALSE 0
#define LENGTH_OF_VOWELS 10

void countConsonantAndVowel(char input[]) {
  char vowels[LENGTH_OF_VOWELS] = "aeiouAEIOU";
  int total_vowels = 0;
  int total_consonants = 0;
  int total_spaces = 0;
  for (int i = 0; input[i] != '\0'; ++i) {
    int flag_vowel = FALSE;
    for (int index = 0; index < LENGTH_OF_VOWELS; ++index) {
      if (input[i] == vowels[index]) {
        total_vowels += INCREMENT;
        flag_vowel = TRUE;
        break;
      }
    }
    if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t') {
      total_spaces += INCREMENT;
    }
    else if (!flag_vowel) {
      total_consonants += INCREMENT;
    }
  }
  // The (total_spaces - 1) at the end is to get rid off of the last new line character that fgets() function adds when pressing enter, as it gets counted as well
  printf("THE VOWELS ARE: %d, THE CONSONANTS ARE: %d, THE WHITE SPACE COUNT: %d\n\n", total_vowels, total_consonants, total_spaces - 1);
}

int main () {
  char INPUT[1000];
  printf("Enter lines to see numbers of vowels, consonants and spaces: \n\n");

  while(fgets(INPUT, sizeof(INPUT), stdin) != NULL) {
    countConsonantAndVowel(INPUT);
  }
  return 0;
}