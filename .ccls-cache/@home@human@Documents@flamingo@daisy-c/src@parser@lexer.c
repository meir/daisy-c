#include "lexer.h"

static char* read_file(const char *path) {
  FILE *file;
  file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file %s\n", path);
    exit(74);
  }

  fseek(file, 0l, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read %s\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file %s\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';

  fclose(file);
  return buffer;
}

Lexer* new_lexer(const char *source) {
  Lexer *lexer = malloc(sizeof(Lexer));
  if (lexer == NULL) {
    fprintf(stderr, "Not enough memory to create lexer\n");
    exit(74);
  }

  lexer->buffer = (char*) read_file(source);
  lexer->current = lexer->buffer;
  return lexer;
}

char next_char(Lexer* lexer) {
  return *lexer->current++;
}

KeywordType check_keyword_ahead(Lexer* lexer) {
  char* start = lexer->current;
  for(int64_t i = 0; i < KEYWORD_COUNT; i++) {
    char* keyword = (char*) KEYWORDS[i];
    while(*keyword != '\0' && *keyword == *start) {
      keyword++;
      start++;
    }

    if(*keyword == '\0') {
      lexer->current = start;
      return (KeywordType) i;
    }else {
      start = lexer->current;
    }
  }
  return INVALID_TYPE;
}

TokenType check_token_type(Lexer* lexer) {
  char c = next_char(lexer);
  switch(c) {
    case '[': return LBracket;
    case ']': return RBracket;
    case '{': return LCurly;
    case '}': return RCurly;
    case '(': return LParen;
    case ')': return RParen;

    case '.': return DOT;
    case ',': return COMMA;
    case ';': return SEMICOLON;

    case '=': return Equal;
    case '-': return Minus;
    case '+': return Plus;
    case '*': return Multiply;
    case '/': return Divide;

    case '>': return Higher;
    case '<': return Lower;

    case '"': return Quote;
    case '\'': return SingleQuote;

    default: return Other;
  }
}

Token* next_token(Lexer* lexer) {
  if (*lexer->current == '\0') {
    return NULL;
  }
  char* start = lexer->current;

  KeywordType kw = check_keyword_ahead(lexer);
  if(kw != INVALID_TYPE) {
    Token* token = malloc(sizeof(Token));
    int64_t length = lexer->current - start;
    token->type = Keyword;
    token->keyword_type = kw;

    token->raw = start;
    token->length = length;
    return token;
  }

  TokenType type = check_token_type(lexer);
  Token* token = malloc(sizeof(Token));
  token->type = type;

  token->raw = start;
  token->length = 1;
  return token;
}

