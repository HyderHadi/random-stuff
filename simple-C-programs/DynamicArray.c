#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  // Using the heap exercise

  char buffer[1000];
  int string_legnth = 0;
  int *arr = NULL;
  int tmp_arr_value = 0;
  size_t size_of_arr = 0;
  int final_sum_result = 0;
  int largest_elemnt = 0;
  int input;
  int found = 0;

  arr = malloc(sizeof(int));

  printf("Get me bunch of numbers to sum it up all together (Enter q to see "
         "result) [You can also search for a value you entered after seeing "
         "the result (also press q to exit completely)]\n");

  while (scanf("%s", buffer) == 1) {

    if (buffer[0] == 'q') {
      break;
    }

    tmp_arr_value = 0;

    // convert ASCII to intgers
    for (int i = 0; buffer[i] != '\0'; i++) {
      int tmp = buffer[i];
      tmp = tmp - '0';
      tmp_arr_value = tmp_arr_value * 10 + tmp;
    }

    arr[size_of_arr] = tmp_arr_value;

    // reallocate for a new growing arr
    int *tmp = realloc(arr, (size_of_arr + 1) * sizeof(int));
    if (!tmp) {
      return 1;
    }
    arr = tmp;
    size_of_arr++;
  }

  for (int i = 0; arr[i] != '\0'; i++) {
    final_sum_result += arr[i];
  }

  // finding the largest element in an array
  for (int i = 0; arr[i] != '\0'; i++) {
    if (largest_elemnt < arr[i]) {
      largest_elemnt = arr[i];
    }
  }

  // reverse the array
  // finding the length of the array
  int arr_len = 0;
  for (int i = 0; arr[i] != '\0'; i++) {
    arr_len++;
  }

  printf("THE RESULT IS [%d]\n", final_sum_result);
  printf("The largest value Entered was [%d]\n", largest_elemnt);

  // reversing the array

  int *rev_arr = malloc(sizeof(*rev_arr) * arr_len);
  for (int i = 0; arr[i] != '\0'; i++) {
    rev_arr[i] = arr[arr_len - 1];
    arr_len--;
  }

  // printing the array in reverse
  printf("The array in reverse is ");
  for (int i = 0; rev_arr[i] != '\0'; i++) {
    printf("%d ", rev_arr[i]);
  }

  printf("\n");

  while (scanf("%s", buffer) == 1) {

    if (buffer[0] == 'q') {
      break;
    }

    tmp_arr_value = 0;

    // convert ASCII to intgers
    for (int i = 0; buffer[i] != '\0'; i++) {
      int tmp = buffer[i];
      tmp = tmp - '0';
      tmp_arr_value = tmp_arr_value * 10 + tmp;
    }

   for(int i = 0;arr[i] != '\0';i++) {
      if(tmp_arr_value == arr[i]) {
        found = tmp_arr_value;
      }
    }
    if(found == 0) {
      printf("Value not found\n");
    }
    else if (found != 0) {
      printf("The value is found within the array\n");
      found = 0;
    }
  }
  free(arr);
  free(rev_arr);
  return 0;
}