#pragma once

#include <stdlib.h>

typedef enum {
  LBracket,   // [
  RBracket,   // ]
  LCurly,     // {
  RCurly,     // }
  LParen,     // (
  RParen,     // )

  DOT,        // .
  COMMA,      // ,
  SEMICOLON,  // ;

  Equal,      // =
  Minus,      // -
  Plus,       // +
  Multiply,   // *
  Divide,     // /

  Higher,     // >
  Lower,      // <
  
  Quote,      // "
  SingleQuote,// '

  Keyword,

  Other,
} TokenType;

typedef enum {
  TypeString,
  TypeNumber,
  TypeBoolean,

  KEYWORD_COUNT,
  INVALID_TYPE = -1
} KeywordType;

#define cstr(str) str "\0"

static const char* KEYWORDS[KEYWORD_COUNT] = {
  [TypeString] = cstr("str"),
  [TypeNumber] = cstr("num"),
  [TypeBoolean] = cstr("bool"),
};

typedef struct {
  TokenType type;
  KeywordType keyword_type;

  char* raw;
  int64_t length;
} Token;
