#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "token.h"
#include "lexer.h"

typedef void (ASTNodeFn)(void);

struct ASTBody;

typedef struct {
  ASTNodeFn* fn;
  struct ASTBody* body;

  Token* token;
  int position;
} ASTNode;

struct ASTBody {
  ASTNode** nodes;
  int32_t count;
};

typedef struct ASTBody ASTBody;

ASTNode* parse_file(char* src);
int sequence_match(Lexer *lexer, ...);
