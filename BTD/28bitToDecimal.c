# include <stdio.h>

# define bitvalue_length 27

unsigned long int powerOFtwo(int value) {
  unsigned long int result = 1;
  for (int i = value;i > 0;i--) {
    result *= 2;
  }
  return result;
}

int main () {
  printf("28-bit binary number converter to decimal:\n\n");
  char bitvalue[28];
  scanf("%s", bitvalue);
  unsigned long int decimalValue = 0;
  for (int i = bitvalue_length;i >= 0;i--) {
    if (bitvalue[i] == '0') {
      decimalValue += 0;
    }
    else if (bitvalue[i] == '1') {
      unsigned long int tmp = powerOFtwo(bitvalue_length - i);
      decimalValue += tmp;
    }
  }

  printf("%lu\n" , decimalValue);

  return 0;
}