#include "../include/tree.h"
#include "../include/parser.h"

struct ntree *new_ntree(char *word, enum token_parser token)
{
  struct ntree *res = malloc(sizeof (struct ntree));
  if (!res)
    return NULL;
  res->name = malloc(sizeof (strlen(word)) * sizeof (char));
  res->token = token;
  strcpy(res->name, word);
  res->size = 0;
  res->sons = NULL;
  return res;
}

struct ntree *add_ntree(struct ntree *tree, struct ntree *son)
{
  if (!son)
    return tree;
  if (!tree)
    return son;
  tree->sons = realloc(tree->sons, sizeof (struct ntree) * tree->size + 1);
  tree->sons[tree->size] = son;
  tree->size++;
  return tree;
}

struct ntree *pop(struct file *f)
{
  if (!f)
    return NULL;

  struct file *rem = f;
  while (f->next)
  {
    rem = f;
    f = f->next;
  }
  struct ntree *tree = f->tree;
  rem->next = NULL;
  free(f);
  if (f == rem && strcmp(tree->name, "\n") == 0)
    return NULL;
  return tree;
}

struct file *push(struct file *f, struct ntree *t)
{
  struct file *new = malloc (sizeof (struct file));
  new->tree = t;
  new->next = f;
  return new;
}

void create_dot(struct ntree *ntree)
{
  if (!ntree)
    return;
  FILE *fd = fopen("mondot.dot", "w+");
  fprintf(fd, "%s", "digraph {\n");
  if (ntree->size > 0)
    print_ast(fd, ntree, 0);
  else
    fprintf(fd, "\"%s\"\n", ntree->name); 
  fprintf(fd, "%s", "}");
  fclose(fd);
}

int print_ast(FILE *fd, struct ntree *tree, int r)
{
  const char* token[] = {"LIST", "AND_OR", "PIPELINE", "GROUP", "FUNCTION",
    "REDIRECTION", "WORD", "ASSIGNMENT_WORD", "NAME", "NEWLINE", "IO_NUMBER",
    "OPERATOR", "RESERVED_WORD", "COMMAND" };
  int rmax = r;
  for (unsigned i = 0; i < tree->size; i++)
  {
    fprintf(fd, "\"%d.%s (%s)\" -> \"%d.%s (%s)\"\n", 
        r, tree->name, token[tree->token], 
        rmax + i + 1, tree->sons[i]->name, token[tree->sons[i]->token]);
    if (tree->sons[i]->size > 0)
      rmax = print_ast(fd, tree->sons[i], rmax + i + 1);
  }
  return rmax + tree->size - 1;
}

void my_print_ntree(struct ntree *tree, struct file *my_file)
{
  create_dot(tree);
  my_file = push(my_file, tree);
  struct ntree *treee = new_ntree("\n", WORD);
  struct ntree *treei = new_ntree("endfils", WORD);
  my_file = push(my_file, treee);
  while (my_file)
  {
    struct ntree *curr = pop(my_file);
    if (!curr)
      return;
    if (strcmp(curr->name, "endfils") == 0)
    {
      printf("//");
      continue;
    }
    if (strcmp(curr->name, "\n") == 0)
    {
      printf("\n");
      my_file = push(my_file, treee);
      continue;
    }
    printf("%s . ", curr->name);
    for (unsigned i = 0; i < curr->size; i++)
      my_file = push(my_file, curr->sons[i]);
    my_file = push(my_file, treei);
  }
}
