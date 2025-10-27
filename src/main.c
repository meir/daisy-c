#include <stdio.h>

#include "parser/lexer.h"

int main() {
  Lexer* lexer = new_lexer("./example.ds");

  char c = next_char(lexer);
  while (c != '\0') {
    fprintf(stdout, "%c", c);
    c = next_char(lexer);
  }

  free(lexer);

  return 0;
}
