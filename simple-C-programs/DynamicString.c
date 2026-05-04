#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    printf("Echo function:: Write something to ECHO: ");


    char *Dynamic_string = NULL;
    size_t string_length = 20;
    Dynamic_string = malloc(string_length);
    
    int input;
    int ch_count = 0;
    while((input = getchar()) != '\n' && input != EOF) {
        Dynamic_string[ch_count] = input;
        ch_count++;

        if(ch_count > (string_length - 5)) {
            string_length *= 2;
            char *tmp = realloc(Dynamic_string, string_length);
            if(!tmp) {
                printf("Allocation failed!\n");
                free(Dynamic_string);
                return 0;
            }

            Dynamic_string = tmp;

        }
    }


    Dynamic_string[ch_count] = '\0';
    printf("%s\n", Dynamic_string);
    free(Dynamic_string);

    return 0;
}