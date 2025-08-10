# include <stdio.h>

void countConsonantandVowel(char input[1000]) {
  char vowels[10] = "aeiouAEIOU";
  int count_vowels = 0;
  int count_consonants = 0;
  int spaces = 0;
  for (int i = 0; input[i] != '\0'; ++i) {
    int flag_vowel = 0;
    for (int n = 0; n < 10; ++n) {
      if (input[i] == vowels[n]) {
        count_vowels += 1;
        flag_vowel = 1;
        break;
      }
    }
    if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t') {
      spaces += 1;
    }
    else if (!flag_vowel) {
      count_consonants += 1;
    }
  }
  printf("THE VOWELS ARE: %d, THE CONSONANTS ARE: %d, THE WHITE SPACE COUNT: %d\n\n", count_vowels, count_consonants, spaces);
}

int main () {
  char INPUT[1000] = "hyder hadi abd-alghani";
  countConsonantandVowel(INPUT);
  return 0;
}