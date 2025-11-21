
#include "parser.h"

ASTNode* parse_file(char* src) {
  Lexer* lexer = new_lexer(src);

  Token* token;
  do {

    if(sequence_match(lexer, 
                      &(Token){.type=Keyword, .keyword_type=TypeInt},
                      &(Token){.type=Identifier},
                      &(Token){.type=Equal},
                      NULL)) {
      fprintf(stdout, "Matched variable declaration\n");
    }else{
      fprintf(stdout, "No match\n");
    }
  } while(token != NULL);

  free(lexer);
  return NULL;
}

int sequence_match(Lexer *lexer, ...) {
  va_list args;
  va_start(args, lexer);
  char* start = lexer->current;

  Token* current_token;
  Token* sequence_token;
  do {
    current_token = next_token(lexer, 1);
    sequence_token = va_arg(args, Token*);

    if(current_token == NULL || sequence_token == NULL) {
      lexer->current = start;
      va_end(args);
      return 0;
    }

    if(current_token->type != sequence_token->type) {
      lexer->current = start;
      va_end(args);
      return 0;
    }

    if(current_token->type == Keyword) {
        if(current_token->keyword_type != sequence_token->keyword_type) {
          lexer->current = start;
          va_end(args);
          return 0;
        }
    }
  }while(sequence_token != NULL && current_token != NULL);

  lexer->current = start;
  va_end(args);
  return 1;
}
