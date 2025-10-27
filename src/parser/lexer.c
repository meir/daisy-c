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

