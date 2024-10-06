#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

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
  List* newList = init_history();
  add_history(newList, "Hello");
  add_history(newList, "World");
  print_history(newList);
  printf("%s", get_history(newList, 1));
  return 1;
}
