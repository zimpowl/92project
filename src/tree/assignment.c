#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

///////////////delete me later
//how to use all that ??
//to add a word to the global big_btree you need to call add_word
//to delete a word use delete_word(char *name)
//search_word(char *name) eturn the struct word associated to the name 
//or NULL if not found.
// print_words(void) to print in the deep left hand format





//create a new btree using struct word
struct btree *new_btree(struct word *word, struct btree *left, struct btree *right)
{
  struct btree *res = malloc(sizeof (struct btree));
  if (!res)
    return NULL;
  res->left = left;
  res->right = right;
  res->word = word;
  return res;
}

//return a new struct word from a token, a name, a value
struct word *new_word(enum token_parser *token, char *name, char *value)
{ 
  struct word *word = malloc(sizeof (struct word));
  if (!word)
    return NULL;
  word->token = token;
  word->name = name;
  word->value = value;
  return word;
}

//recurcive part of add_word
struct btree *add_word_rec(struct btree *btree, struct word *word)
{
  if (!btree)
    return new_btree(word, NULL, NULL);
  else
  {
    if (strcmp(word->name, btree->word->name) < 0)
      btree->left = add_word_rec(btree->left, word); 
    else
      btree->right = add_word_rec(btree->right, word); 
    return btree;
  }
}

// create a word from parameters and add it to the btree
//do nothing and return 0 if everithing ok or word allready exits
//return 1 if error
int add_word(enum token_parser *token, char *name, char *value)
{
  if (search_word(name);
    return 0;
  struct word *word = new_word(token, name, value);
  if (!word)
    return 0;
  else
    big_btree = add_word_rec(big_btree, word);
  return 1;
}

//from delete function
struct btree *delete_max(struct btree *btree)
{
  if (!btree->right)
    return btree;
  if (!btree->right->right)
    return btree;
  else
    return delete_max(btree->right); 
}

//from delete function
struct btree *del_btree(struct btree *btree)
{
  struct btree *res = btree;
  if (!btree->right && !btree->left)
   res = NULL;
  else if (!btree->right)
    res = btree->left;
  else if (!btree->left)
    res = btree->right;
  else
  {
    res = delete_max(btree->left);
    if (res == btree->left)
      res->right = btree->right;
    else
    {
      struct btree *tmp2 = res->right;
      res->word->name = tmp2->word->name;
      res->right = tmp2->left;
      free(tmp2->word);
      free(tmp2);
    }
  }
  free(btree);
  return res;
}

//reccursive part of delete 
struct btree *delete_word_rec(struct btree *btree, char *name)
{
    int cmp = strcmp(name, btree->word->name);
    if (cmp < 0)
      btree->left = delete_word_rec(btree->left, name);
    else
    {
      if (cmp > 0)
       btree->right = delete_word_rec(btree->right, name);
      else
        btree = del_btree(btree);
    }
  return btree;
}

//delete a btree from big_btree using a name
void delete_word(char *name)
{
  if (!big_btree)
    return;
  else
    big_btree = delete_word_rec(big_btree, name);
}


//recurrsive part of search function
struct btree *search_word_rec(struct btree *btree, char *name)
{
  if (!btree)
    return NULL;
  else
  {
    int cmp = strcmp(name, btree->word->name);
    if (cmp == 0)
      return btree;
    else
    {
      if (cmp < 0)
        return search_word_rec(btree->left, name);
      else
        return search_word_rec(btree->right, name);
    }
  }
}

// return a struct word corresponding to the name searched
struct word *search_word(char *name)
{
  if (!big_btree)
    return NULL;
  struct btree *res = search_word_rec(big_btree, name);
  if (!res)
    return NULL;
  return res->word;
}

//reccursive part of destroy function
struct btree *destroy_words_rec(struct btree *btree)
{
  if (btree)
  {  
    btree->right = destroy_words_rec(btree->right);
    btree->left = destroy_words_rec(btree->left);
    free(btree->word);
    free(btree);
  }
  return NULL;
}
  
//remove all the big_btree and free everything
void destroy_words(void)
{
  big_btree = destroy_words_rec(big_btree);
}


//allow to print each word found in the deep left hand way
void print_btree(struct btree *tree)
{
  if (!tree)
    return;
  printf("%s  %s \n", tree->word->name, tree->word->value);
  print_btree(tree->left);
  print_btree(tree->right);
}


int main(void)
{
  add_word(0, "f", "ok");
  add_word(0, "g", "ok");
  add_word(0, "h", "ok");
  add_word(0, "n", "ok");
  add_word(0, "l", "ok");
  add_word(0, "o", "ok");
  add_word(0, "w", "ok");
  add_word(0, "m", "ok");
  add_word(0, "x", "ok");
  add_word(0, "y", "ok");
  print_btree(big_btree); //1
  printf("\n");
  search_word("eee");
  printf("f %s\n", (search_word("f"))->name);  
  printf("g %s\n", (search_word("g"))->name);  
  printf("h %s\n", (search_word("h"))->name);  
  printf("n %s\n", (search_word("n"))->name);  
  printf("l %s\n", (search_word("l"))->name);
  printf("o %s\n", (search_word("o"))->name);
  printf("w %s\n", (search_word("w"))->name);
  printf("m %s\n", (search_word("m"))->name);
  printf("x %s\n", (search_word("x"))->name);
  printf("y %s\n", (search_word("y"))->name);
  printf("\n");
  delete_word("n");
  delete_word("f");
  print_btree(big_btree); //2
  delete_word("g");
  delete_word("o");
  delete_word("y");
  print_btree(big_btree);  //3
  destroy_words();
  print_btree(big_btree);  //4
  printf("printed after destroy\n");
  return 0;
}







