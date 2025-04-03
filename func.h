#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#define uint uint8_t

int check_word(char*); // cheack the validity of the word
bool he_exit(); // asking the user for termianting the program
uint* construct_result(char*, int); // return the result array
void handle_input(char*, int); // restrict input length
void assign_parities(uint*, int); // assign parity values
