# include <stdio.h>

# define HexBase 16

int HexadecimalToInteger(char string[]) {

    // The standalone Number *10* here in the FOR LOOP is a complementary value to make the hexadecimal function output correct values.

    int DecimalNumberTotal = 0;

    for (int i = 0;string[i] != '\0'; ++i) {
      if (string[i] >= '0' && string[i] <= '9') {
        DecimalNumberTotal = HexBase * DecimalNumberTotal + string[i] - '0';
      }
      else if (string[i] >= 'a' && string[i] <= 'f') {
        DecimalNumberTotal = HexBase * DecimalNumberTotal + (string[i] - 'a' + 10);
      }
      else if (string[i] >= 'A' && string[i] <= 'F') {
        DecimalNumberTotal = HexBase * DecimalNumberTotal + (string[i] - 'A' + 10);
      }
    }
    return(DecimalNumberTotal);
}

// THE MAIN BLOCK

int main () {
    char TheHexString[1000];
    printf("Give me a Hexadecimal to convert (Without the prefix 0x)\n\n");

    while (scanf("%s", &TheHexString) != EOF) {

        int res = HexadecimalToInteger(TheHexString);
        printf("The result is :  %d\n\n", res);

    }
    return 0;
}