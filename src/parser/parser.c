
#include "parser.h"

ASTNode* parse_file(char* src) {
  Lexer* lexer = new_lexer(src);

  Token* token;
  do {
    token = next_token(lexer);

    char* raw = token->raw;
    for(int64_t i = 0; i < token->length; i++) {
      fprintf(stdout, "%c", *raw);
      raw++;
    }

    free(token);
  } while(token != NULL);

  free(lexer);
  return NULL;
}
