# include <stdio.h>

int GreatestCommonDivisor(int INPUT_ONE, int INPUT_TWO) {
    int DIVISOR;
    for (int i = 1; i < INPUT_ONE || i < INPUT_TWO;++i) {
        if (INPUT_ONE % i == 0 && INPUT_TWO % i == 0) {
            DIVISOR = i;
        }
    }
    return DIVISOR;
}


int main() {
    int INPUT_ONE;
    int INPUT_TWO;
    printf("Give me a TWO numbers to find GCD\n");
    while (scanf("%d %d", &INPUT_ONE, &INPUT_TWO) != EOF) {
        int RESULT = GreatestCommonDivisor(INPUT_ONE, INPUT_TWO); 
        printf("%d\n\n", RESULT);
    }
    return 0;
}