#pragma once

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

typedef struct {
  TokenType type;
  char* raw;
} Token;
