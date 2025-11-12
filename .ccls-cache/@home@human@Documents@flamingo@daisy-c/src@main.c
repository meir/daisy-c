
#include "parser/parser.h"

int main() {
  ASTNode* root = parse_file("./example.ds");
  if (root != NULL) {
    free(root);
  }

  return 0;
}
