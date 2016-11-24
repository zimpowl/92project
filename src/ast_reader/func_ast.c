#include "../include/tree.h"
#include "../include/parser.h"
#include "../include/ast_reader.h"
#include "../include/executor.h"


int reg_func_a(struct ntree *ntree)
{
 int res = add_word(ntree->token, ntree->sons[0], ntree->name, NULL);
 if (res == 1)
   return 0;
  return 1;
}
