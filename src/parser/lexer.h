#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "token.h"

typedef struct {
  char *buffer;
  char *current;
} Lexer;

static char* read_file(const char *path);
Lexer* new_lexer(const char *source);
char next_char(Lexer* lexer);

Position* check_keyword(Lexer* lexer);
Position* check_identifier(Lexer* lexer);
Position* check_token(Lexer* lexer);
Position* get_position(Lexer* lexer);

Token* get_token(Lexer* lexer);
Token* next_token(Lexer* lexer, int skip_whitespace);
