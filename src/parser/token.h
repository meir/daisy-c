#pragma once

#include <stdlib.h>
#define cstr(str) str "\0"

typedef enum {
  Whitespace, // ws

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
  
  Identifier, // [A-Za-z_][A-Za-z0-9_]*

  Keyword,

  Other,

  TOKEN_COUNT,
} TokenType;

static const char* TOKENS[TOKEN_COUNT] = {
  [Whitespace] = cstr(" \n\t"),
  [LBracket] = cstr("["),
  [RBracket] = cstr("]"),
  [LCurly] = cstr("{"),
  [RCurly] = cstr("}"),
  [LParen] = cstr("("),
  [RParen] = cstr(")"),
  [DOT] = cstr("."),
  [COMMA] = cstr(","),
  [SEMICOLON] = cstr(";"),
  [Equal] = cstr("="),
  [Minus] = cstr("-"),
  [Plus] = cstr("+"),
  [Multiply] = cstr("*"),
  [Divide] = cstr("/"),
  [Higher] = cstr(">"),
  [Lower] = cstr("<"),
  [Quote] = cstr("\""),
  [SingleQuote] = cstr("'"),

  [Identifier] = cstr(""),
  [Keyword] = cstr(""),
  [Other] = cstr(""),
};

typedef enum {
  TypeString,
  TypeInt,
  TypeFloat,
  TypeBoolean,
  TypeFunction,
  TypeMap,
  TypeList,

  KEYWORD_COUNT,
  INVALID_TYPE = -1
} KeywordType;

static const char* KEYWORDS[KEYWORD_COUNT] = {
  [TypeString] = cstr("str"),
  [TypeInt] = cstr("int"),
  [TypeFloat] = cstr("float"),
  [TypeBoolean] = cstr("bool"),
  [TypeFunction] = cstr("func"),
  [TypeMap] = cstr("map"),
  [TypeList] = cstr("list"),
};

typedef struct {
  char* start;
  int64_t length;
} Position;

typedef struct {
  TokenType type;
  KeywordType keyword_type;

  Position* position;
} Token;

