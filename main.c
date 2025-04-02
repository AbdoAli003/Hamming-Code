#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 256

int main(int argc, char *argv[]) {
  char stored_word[MAX_SIZE + 1];
  char fetched_word[MAX_SIZE + 1];
  int M, K, res_len;
  int num;
  int x = 4;
  while (1) {
    x = 4;
    memset(stored_word, 0, MAX_SIZE + 1);
    memset(fetched_word, 0, MAX_SIZE + 1);
    printf(
        "Enter the stored word in binary format (Maximum size = 256 bits):\n");
    if (fgets(stored_word, MAX_SIZE + 1, stdin) == NULL) {

      printf("Input Error!\n");
      continue;
    }
    handle_input(stored_word, MAX_SIZE);
    printf("%s\n", stored_word);
    if (!check_word(stored_word)) {

      if (he_exit())
        break;
      continue;
    }
    M = strlen(stored_word);
    if (M == 0)
      continue;
    for (K = 2; x < M + K + 1; K++) {
      x *= 2;
    }
    res_len = M + K;
    printf("K = %d, M = %d\n\n", K, M);
    uint *result1 = construct_result(stored_word, res_len);
    assign_parities(result1, res_len);
    printf("Word will be stored as :\n");
    for (int i = res_len - 1; i >= 0; i--)
      printf("%d", result1[i]);
    printf("\n");
    while (1) {
      printf("Enter the fetched word:\n");

      if (fgets(fetched_word, MAX_SIZE + 1, stdin) == NULL) {
        printf("Input Error!\n");
        continue;
      }
      handle_input(fetched_word, MAX_SIZE);
      if (!check_word(fetched_word) || strlen(fetched_word) != M)
        printf("That does not match the stored word format !\nPlease try "
               "again:\n");
      else
        break;
    }
    printf("%s\n", fetched_word);
    uint *result2 = construct_result(fetched_word, res_len);
    assign_parities(result2, res_len);

    printf("Word will be fetched as :\n");
    for (int i = res_len - 1; i >= 0; i--)
      printf("%d", result2[i]);
    printf("\n");
    uint parity[K];
    int j = 0;
    int high;
    int bit = 0;
    for (int i = 1; i <= res_len; i *= 2) {
      parity[j] = result1[i - 1] ^ result2[i - 1];
      high |= parity[j++];
    }
    for (int i = K - 1; i >= 0; i--)
      printf("%d", parity[i]);
    printf("\n");
    if (!high)
      printf("No Error occured\n");
    else {
      for (int i = 0, b = 1; i < K; i++, b *= 2) {
        bit = parity[i] ? bit + b : bit;
      }
      if (result1[bit - 1] == result2[bit - 1])
        printf("The error is in more than one bit!\n");
      else {
        printf("Error occured at bit position : %d\n", bit);
        if (!(bit & (bit - 1)))
          printf("No error occured at data bit\n");
        else {
          // find the data bit position
          int idx = 0;
          for (int i = 0; i < bit; i++) {
            int j = i + 1;
            if (j & (j - 1))
              idx++;
          }
          printf("Error occured at data bit %d\n", idx);
          result2[bit - 1] = !result2[bit - 1];
          printf("Word after correction :\n");
          for (int i = res_len - 1; i >= 0; i--)
            printf("%d", result2[i]);
          printf("\n");
        }
      }
    }
    free(result1);
    free(result2);
  }

  return 0;
}
