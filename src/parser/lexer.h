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
