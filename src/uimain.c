#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int main() {
  char input[30];
  puts("> Awaiting user input.");
  fgets(input, 30, stdin);
  printf("\n%s", input);
  printf("Number of tokens in input: %d\n", count_tokens(input));
  char *updStr = copy_str(input, sizeof(input));
  printf(updStr);
  printf("Number of tokens for new string: %d\n", count_tokens(updStr));
  char **toke = tokenize(updStr);
  free(updStr);
  print_tokens(toke);
  return 1;
}
