#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char word_picker(char *array, int randomness, char *picked_word) {
    int space_counter = -1;
    int last_space = 0;
    int iterator = 0;
    for(int i = 0;array[i] != '\0';i++) {
        if(array[i] == ' ') {
            space_counter++;
            if(space_counter == randomness) {
                last_space = i;
                break;
            }
        }
    }
    for(int i = last_space + 1;array[i] != ' ';i++) {
        picked_word[iterator] = array[i];
        iterator++;
    }
    return *picked_word;
}

char word_omitter(char *word, char *array_input, char *letters) {
    int iterator = 0;
    srand(time(NULL));
    int len = strlen(array_input);
    if ((len % 2) == 0) {
        for(int i = 0;i < len;i++) {
            int tmp = i + rand() % len;
            if(word[i + tmp] != '\0') {
                letters[iterator] = word[i + tmp];
                word[i + tmp] = '*';
                iterator++;
                if (iterator == 2) {
                    break;
                }
            }
        }
    }
    else if ((len % 2) != 0) {
        for(int i = 0;i < len;i++) {
            int tmp = i + rand() % len;
            if(word[i + tmp] != '\0') {
                letters[iterator] = word[i + tmp];
                word[i + tmp] = '*';
                iterator++;
                if (iterator == 3) {
                    break;
                }
            }
        }
    }
    return *word;
}
int main()
{
    char *words = " word steal steel dog kitten fire tree folklore elden ring monopoly knee calf grace shit bastard shaft shift hole ace dread death dance";
    char picked_word[10];
    char letters[5];
    char omitted_word[10];
    char user_input[10];
    int ite = 0;
    int attempts = 5;
    srand(time(NULL));
    word_picker(words, rand() % 23, picked_word);
    picked_word[strcspn(picked_word, " ")] = '\0';
    picked_word[strcspn(picked_word, "\n")] = '\0';
    strcpy(omitted_word, picked_word);
    word_omitter(omitted_word, picked_word, letters);
    printf("A word has been picked: (%s) guess it or the man get HANGED!\n", omitted_word);
    while(fgets(user_input, sizeof(user_input), stdin) != NULL) {
        user_input[strcspn(user_input, "\n")] = '\0';
        for(int i = 0;user_input[i] != '\0';i++) {
            if(omitted_word[i] == '*') {
                if(user_input[i] == letters[ite]) {
                    omitted_word[i] = letters[ite];
                    ite++;
                    
                }
            }
        }
        if(strcmp(user_input, picked_word) == 0) {
                printf("Saved! The man wasnt hanged :)\n");
                break;
            }
            
            if(attempts > 0) {
                attempts--;
                printf("You have %d more times\nKeep going the word now is %s\n", attempts, omitted_word);
            }
            if(attempts == 0) {
                printf("The man was hanged! =)\n");
                printf("The actual word is: %s\n", picked_word);
                break;
            }
    }
    return 0;
}