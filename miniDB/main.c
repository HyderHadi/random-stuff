#include "HashMap.h"
#include "db_commands.h"
#include <stdio.h>




int main() {

    struct hashTable *t1 = createTable();
    FILE *fh = NULL;
    printf("Enter a filename for the database, otherwise press ENTER: ");
    char *fileName = read_line();
    if(!fileName) {
        fileName = "db.txt";
        printf("Default name picked up: %s\n", fileName);
    }


    int exitState = -1;
    while (db_commands(t1, fh, fileName) != exitState) {
        printf("");
    }

    t1->destructor(t1);

    return 0;
}
