#include "func.h"
#include <stdio.h>
#include <string.h>

int check_word(char *swd) {

  int word_len = strlen(swd);
  for (int i = 0; i < word_len; i++) {
    if (swd[i] != '0' && swd[i] != '1') {

      printf("Word is not valid!\n");
      return 0;
    }
  }
  return 1;
}

bool he_exit() {
  char c;
  printf("Would you like to exit ? (Y/n) : ");
  while (scanf("%c", &c)) {
    getchar();
    if (c == 'Y' || c == 'y')
      return true;
    if (c == 'N' || c == 'n')
      break;
  }
  return false;
}

uint *construct_result(char *swd, int tot_len) {
  uint *result = (uint *)malloc(sizeof(uint) * tot_len);
  int cnt = 0; // index for input word array
  for (int i = tot_len - 1; i >= 0; i--) {
    int j = i + 1;
    if (!(j & (j - 1))) // power of 2
      result[i] = 0;
    else
      result[i] = swd[cnt++] - '0';
  }
  return result;
}

void handle_input(char *buffer, int mx_size) {
  if (strchr(buffer, '\n') == NULL) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return;
  }
  buffer[strlen(buffer) - 1] = '\0';
}

void assign_parities(uint *result, int tot_len) {

  for (int i = tot_len - 1; i >= 0; i--) {
    for (int j = 1; j <= tot_len; j *= 2) {
      if (i + 1 != j && (i + 1) & j) {
        result[j - 1] ^= result[i];
      }
    }
  }
}
