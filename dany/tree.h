#ifndef TREE_H
#define TREE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file tree.h
 */



/**
 * @enum token_parser
 * @brief Enumeration of the token generated by the ast tree.
 */
enum token_parser
{
  LIST,
  AND_OR,
  PIPELINE,
  GROUP,
  FUNCTION,
  REDIRECTION,
  WORD,
  ASSIGNMENT_WORD,
  NAME,
  NEWLINE,
  IO_NUMBER,
  OPERATOR,
  RESERVED_WORD,
  COMMAND,
  TEST
};

/**
 * @struct ntree
 * @brief Represent the tree ast structure created by the parser.
 */
struct ntree
{
  char *name;
  enum token_parser token;
  struct ntree **sons;
  unsigned size;
};

struct word
{
  enum token_parser *token;
  char *name;
  char *value;
};

struct btree
{
  struct btree *left;
  struct btree *right;
  struct word *word;
};

//global btree where every struct word are stored
struct btree *big_btree;



/**
 * @struct file
 * @brief Created to display the ast tree line per line.
 */
struct file
{
  struct ntree *tree;
  struct file *next;
};



//if sucess to add word return 1 else return 0
int add_word(enum token_parser *token, char *name, char *value);

//delete word from name, do nothing if not found
void delete_word(char *name);

//return the struct word associated to the name or NULL if not found
struct word *search_word(char *name);

//print all word found on the terminal
void print_words(void);


/**
 * @fn struct ntree *new_ntree(char *word, enum token_parser token)
 * @param word to put in the node.
 * @param token the enum to describe the type of the word.
 * @brief create a new tree.
 * @return return the new tree.
 */
struct ntree *new_ntree(char *word, enum token_parser token);

/**
 * @fn struct ntree *add_ntree(struct ntree *tree, struct ntree *son);
 * @param tree the father of the futur tree.
 * @param son the son of the tree given in param.
 * @brief Add son to the others sons of the father.
 * @return return the new tree.
 */
struct ntree *add_ntree(struct ntree *tree, struct ntree *son);

/**
 * @fn void my_print_ntree(struct ntree *tree, struct file *myfile);
 * @param tree the tree reference.
 * @param son the file to display the tree in order.
 * @brief Print the tree ast.
 */


void my_print_ntree(struct ntree *tree, struct file *myfile);

/**
 * @fn struct ntree *pop(struct file *f);
 * @param file the file to pop a node from tree ast.
 * @brief Pop the last element push to the current file.
 * @return return the ntree push at last.
 */
struct ntree *pop(struct file *f);

/**
 * @fn struct file *push(struct file *f, struct ntree *t);
 * @param file the file to push a node tree.
 * @param t the ntree to push in the file.
 * @brief Push a tree ast in the file at the last.
 * @return return the file.
 */
struct file *push(struct file *f, struct ntree *t);

/**
 * @fn struct file *push(struct file *f, struct ntree *t);
 * @param file the file to push a node tree.
 * @param t the ntree to push in the file.
 * @brief Push a tree ast in the file at the last.
 * @return return the file.
 */
void create_dot(struct ntree *ntree);

/**
 * @fn struct file *push(struct file *f, struct ntree *t);
 * @param file the file to push a node tree.
 * @param t the ntree to push in the file.
 * @brief Push a tree ast in the file at the last.
 * @return return the file.
 */
int print_ast(FILE *fd, struct ntree *tree, int r);

/*struct btree
{
  struct btree *left;
  struct btree *right;
  char *name;
  char *value;
};

struct btree *add_btree(struct btree *tree, char *name, enum token_parser tok);
struct btree *search_btree(struct btree * tree, char *name);
struct btree *delete_btree(struct btree *tree, char *name);


struct btree *add_btree(struct btree *tree, char *name);
struct btree *search_btree(struct btree * tree, char *value);
struct btree *delete_btree(struct btree *tree, char *value);
void print_btree(struct btree *tree);*/

#endif
