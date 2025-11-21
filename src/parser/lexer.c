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

Position* check_keyword(Lexer* lexer) {
  char* start = lexer->current;
  for(int64_t i = 0; i < KEYWORD_COUNT; i++) {
    char* keyword = (char*) KEYWORDS[i];
    while(*keyword != '\0' && *keyword == *start) {
      keyword++;
      start++;
    }

    if(*keyword == '\0') {
      int64_t length = start - lexer->current;
      Position* pos = malloc(sizeof(Position));
      pos->start = lexer->current;
      pos->length = length;
      return pos;
    }else {
      start = lexer->current;
    }
  }
  return NULL;
}

Position* check_identifier(Lexer* lexer) {
  char* start = lexer->current;
  if(!((*start >= 'A' && *start <= 'Z') || (*start >= 'a' && *start <= 'z') || *start == '_')) {
      return NULL;
  }

  int64_t i = 1;
  for(i = 1; *(start + i) != '\0'; i++) {
    char* current = start + i;
    if(!((*current >= 'A' && *current <= 'Z') || (*current >= 'a' && *current <= 'z') || (*current >= '0' && *current <= '9') || *current == '_')) {
      break;
    }
  }

  Position* pos = malloc(sizeof(Position));
  pos->start = start;
  pos->length = i;
  return pos;
}

Position* check_token(Lexer* lexer) {
  Position* pos = malloc(sizeof(Position));
  pos->start = lexer->current;
  pos->length = 1;
  return pos;
}

Position* get_position(Lexer* lexer) {
  Position* position = check_keyword(lexer);
  if(position != NULL) {
    return position;
  }
  
  position = check_identifier(lexer);
  if(position != NULL) {
    return position;
  }else{
    return check_token(lexer);
  }
}

Token* get_token(Lexer* lexer) {
  if (*lexer->current == '\0') {
    return NULL;
  }

  Position* position = get_position(lexer);
  Token* token = malloc(sizeof(Token));
  token->position = position;

  switch(position->length) {
    case 1:
      token->type = Identifier;
      for(int64_t i = 0; i < TOKEN_COUNT; i++) {
        char* token_options = (char*) TOKENS[i];
        while(*token_options != '\0') {
          if(*token_options == position->start[0]) {
            token->type = (TokenType) i;
            break;
          }
          token_options++;
        }
      }
      print_token(token);
      return token;
    default:
      token->type = Identifier;

      for(int64_t i = 0; i < KEYWORD_COUNT; i++) {
        char* keyword = (char*) KEYWORDS[i];
        for(int64_t end = 0; end < position->length; end++) {
          if(*(position->start + end) != *(keyword + end)) {
            goto continue_outer;
          }
        }

        token->type = Keyword;
        token->keyword_type = (KeywordType) i;
        break;
continue_outer:;
      }

      print_token(token);
      return token;
  }

  return NULL;
}

Token* next_token(Lexer* lexer, int skip_whitespace) {
  Token* token = get_token(lexer);
  if(token == NULL) {
    return NULL;
  }

  lexer->current += token->position->length;

  if(skip_whitespace) {
    while(token->type == Whitespace) {
      free(token->position);
      free(token);
      token = get_token(lexer);
      if(token == NULL) {
        return NULL;
      }
      lexer->current += token->position->length;
    }
  }

  return token;
}

