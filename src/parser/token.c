
#include "token.h"

void print_token(Token* token) {
  if (token->position == NULL) {
    fprintf(stdout, "[ Static Type: '%d' ]\n", token->type);
    return;
  }

  fprintf(stdout, "[ Token: '");
  for(int64_t i = 0; i < token->position->length; i++) {
    fprintf(stdout, "%c", token->position->start[i]);
  }

  fprintf(stdout, "', Type: '%d' ]\n", token->type);
}
