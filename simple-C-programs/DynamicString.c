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
    while((input = getchar()) != '\n' && input != EOF) {
        
    }




    return 0;
}