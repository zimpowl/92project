#include "../include/tree.h"

struct btree
{
  struct btree *left;
  struct btree *right;
  char *name;
};

struct btree *new_btree(char *name, struct btree *left, struct btree *right)
{
  struct btree *res = malloc(sizeof (struct btree));
  res->left = left;
  res->right = right;
  res->name = name;
  return res;
}

struct btree *add_btree(struct btree *tree, char *name)
{
  if (!tree)
    return new_btree(name, NULL, NULL);
  else
  {
    if (strcmp(name, tree->name) < 0)
      tree->left = add_btree(tree->left, name); 
    else
      tree->right = add_btree(tree->right, name); 
    return tree;
  }
}

struct btree *search_btree(struct btree * tree, char *value)
{
  if (!tree)
    return NULL;
  else
  {
    int cmp = strcmp(value, tree->name);
    if (cmp == 0)
      return tree;
    else
    {
      if (cmp < 0)
        return search_btree(tree->left, value);
      else
        return search_btree(tree->right, value);
    }
  }
}

struct btree *delete_max(struct btree *tree)
{
  if (!tree->right)
    return tree;
  if (!tree->right->right)
    return tree;
  else
    return delete_max(tree->right); 
}

struct btree *delete_min(struct btree *tree)
{
  if (!tree->right->left)
    return tree;
  else
    return delete_max(tree->left); 
}

struct btree *del_btree(struct btree *tree)
{
  struct btree *res = tree;
  if (!tree->right && !tree->left)
   res = NULL;
  else if (!tree->right)
    res = tree->left;
  else if (!tree->left)
    res = tree->right;
  else
  {
    res = delete_max(tree->left);
    if (res == tree->left)
      res->right = tree->right;
    else
    {
      struct btree *tmp2 = res->right;
      tree->name = tmp2->name;
      res->right = tmp2->left;
      free(tmp2);
      return tree;
    }
  }
  free(tree);
  return res;
}


struct btree *delete_btree(struct btree *tree, char *value)
{
  if (tree)
  {
    int cmp = strcmp(value, tree->name);
    if (cmp < 0)
      tree->left = delete_btree(tree->left, value);
    else
    {
      if (cmp > 0)
        tree->right = delete_btree(tree->right, value);
      else
        tree = del_btree(tree);
    }
  }
  return tree;
}

void print_btree(struct btree *tree)
{
  if (!tree)
    return;
  printf("%s ", tree->name);
  //printf(" ");
  print_btree(tree->left);
  print_btree(tree->right);
}


/*int main(void)
{
  struct btree *ptr = add_btree(NULL, "f");
  add_btree(ptr, "t");
  add_btree(ptr, "h");
  add_btree(ptr, "i");
  add_btree(ptr, "e");
  add_btree(ptr, "b");
  add_btree(ptr, "n");
  print_btree(ptr);
  printf("e %s\n", (search_btree(ptr, "e"))->name);  
  printf("n %s\n", (search_btree(ptr, "n"))->name);  
  printf("t %s\n", (search_btree(ptr, "t"))->name);  
  printf("f %s\n", (search_btree(ptr, "f"))->name);  
  printf("b %s\n", (search_btree(ptr, "b"))->name);
  printf("\n");
  ptr = delete_btree(ptr, "n");
  ptr = delete_btree(ptr, "f");
  ptr = delete_btree(ptr, "e");

  print_btree(ptr);
  printf("\n");
  return 0;
}*/
