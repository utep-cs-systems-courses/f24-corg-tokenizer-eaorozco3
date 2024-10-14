#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c) {
  if(c == ' ' || c == '\t') return 1;
  return 0;
}

int non_space_char(char c) {
  if(c == ' ' || c == '\t' || c == '\0' || c == '\n') return 0;
  return 1;
}

// Return a pointer to first non-space character in string.
char *token_start(char *str) {
  for( ; *str; str++) {
    if(non_space_char(*str)) return str;
  }

  return 0;
}

// Return a pointer to first space or terminator character.
char *token_terminator(char *token) {
  for( ; token; token++) {
    if(space_char(*token) || *token == '\0') return token;
  }

  return 0;
}

// Iterate through string and count strings by counting start and end. If empty, return 0.
int count_tokens(char *str) {
  if(!str) return 0;
  int count = 0;
  while(*str) {
    if(!token_start(str)) return count;
    str = token_start(str);
    str = token_terminator(str);
    count++;
  }
  
  return count;
}

// Create a new string and copy contents to other string.
char *copy_str(char *inStr, short len) {
  if(!count_tokens(inStr)) return 0;
  char *newStr = malloc(len);
  int i;
  for(i = 0; *(inStr + i) && i < len; i++) {
    *(newStr + i) = *(inStr + i);
  }

  // Most of the time, allocates space is too much, so reallocate the space.
  char *retStr = realloc(newStr, i);
  *(retStr + i) = '\0';
  return retStr;
}

char **tokenize(char *str) {
  int numTokens = count_tokens(str);
  if(!numTokens) return 0;
  char **tvp, **tokVec;
  tvp = tokVec = calloc(numTokens + 1, sizeof(char *));
  char *start = token_start(str);
  while(start) {
    char *end = token_terminator(start);
    char *tokCopy = copy_str(start, end - start);
    *tvp = tokCopy;
    tvp++;
    start = token_start(end);
  }

  *tvp = 0;
  return tokVec;
}

void print_tokens(char **tokens) {
  if(!tokens) {
    printf("No tokens entered!");
    goto exit;
  }

  for(int i = 0; *tokens; tokens++) {
    printf("%s ", *tokens);
  }

 exit:
  return;
}

// Free all tokens and the pointer that points to them.
void free_tokens(char **tokens) {
  for(; tokens; tokens++) {
    free(*tokens);
  }

  free(tokens);
  return;
}
