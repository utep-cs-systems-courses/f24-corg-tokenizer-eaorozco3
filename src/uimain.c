#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

// Check if characters are digits.
int isDigit(char *str) {
  int result = 0;
  while(*str && ((*str - '0') >= 0 && (*str - '0') <= 9)) {
    result = result * 10 + (int)(*str - '0');
    str++;
  }

  printf("\n%d\t", result);
  return result;
}

int isExit(char *str) {
  char *strExit = "exit";
  while(*str && *strExit) {
    if(*str != *strExit) return 0;
    str++; strExit++;
  }

  return 1;
}

// Using '!', this will check the string for any commands and proceed accordingly.
int isCommand(char *str, List *list) {
  if(*str && *str == '!') {
    str++;
    if(!(*str) || *str == '\n') {print_history(list); goto end;}
    if(isExit(str)) return 1;
    if((*str - '0') >= 1 && (*str - '0') <= 9) {
      char **printer = tokenize(get_history(list, isDigit(str)));
      print_tokens(printer);
      free_tokens(printer);
      goto end;
    }
  }
 
 end:
  return 0;
}

int main() {
  List *newList = init_history();
  while(1) {
    char *input = malloc(300 * sizeof(char));
    puts("\n> Awaiting user input. Type '!' to view history, !# to recover a specified item, and !exit to exit.");
    fgets(input, 300, stdin);
    char *updStr = copy_str(input, 300);
    free(input);
    char **toke = tokenize(updStr);
    // We use the first token to check for commands.
    if(toke) {
      if(isCommand(*toke, newList)) goto end;
      add_history(newList, updStr);
    }
    else puts("No input detected.");
    free_tokens(toke);
  }
 end:
  free_history(newList);
  puts("\nThank you and goodbye!");
  return 1;
}
