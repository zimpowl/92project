#ifndef _HEADER_LEXER_H
#define _HEADER_LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

/**
 * @file header_lexer.h
 */

/**
 * @var g_list
 * @brief struct global where is stocked the current token and the next token
 */
extern struct list_token *g_list;

/**
 * @var g_line
 * @brief string global where is stocked in one line all the command
 */
extern char *g_line;

/**
 * @enum type_token
 * @brief 2 type : OPERATOR and WORD
 */
enum type_token
{
  OPERATOR,
  WORD,
  WORD_DQUOTED,
  WORD_QUOTED
};

/**
 * @struct token
 * @brief token is a string typed
 */
struct token
{
  enum type_token type;
  char *s;
};

/**
 * @struct list_token
 * @brief chained list with 2 token
 */
struct list_token
{
  struct token token;
  struct list_token *next;
  size_t i;   /*! index token in g_line*/
};

/****************** string.c **************/
/**
 * @fn char *append(char *s, char c)
 * @param s String of reference
 * @param c Char to append
 * @brief realloc s to store s append to c
 * @return s append to c
 */
char *append(char *s, char c);
/**
 * @fn void my_delete(char *s, size_t i)
 * @param s String of reference 
 * @param i Index of char to delete
 * @brief delete character s[i] in s and realloc s in consequently
 */
char *my_delete(char *s, int i);
/**
 * @fn void delete_space(char *s)
 * @param s String of reference
 * @brief delete space when there are more than 2 spaces following, 
 */
void delete_space(char *s);
/*******************************************/


/***************** type.c ******************/
/**
 * @fn int is_quoted(char *s, size_t len, enum type_token type)
 * @param s String
 * @param len 
 * @param type
 * @return 1 if s contain quote, 0 otherwise 
 */
int is_quoted(char *s, size_t len, enum type_token type);
/**
 * @fn int is_dquoted(char *s, size_t len, enum type_token type)
 * @return 1 if s contain double quote, 0 otherwise
 */
int is_dquoted(char *s, size_t len, enum type_token type);
/**
 * @fn int is_operator(char *tmp)
 * @param tmp String
 * @brief compare tmp with each operator of the language
 * @return 1 if tmp is an operator, 0 otherwise
 */
int is_operator(char *tmp);
/**
 * @fn enum type_token take_type(char *s, char c, enum type_token type)
 * @param s String of the current token
 * @param c Next char in g_line
 * @param type type of the current token
 * @brief append s c and check different rules that determinate the next type
 * @return new type of the potential new token
 */
enum type_token take_type(char *s, char c, enum type_token type);
/********************************************/


/***************** check.c *****************/
int search_dquoted(char *s, int start);

int search_quoted(char *s, int start);
/**
 * @fn void check_delete_end(struct list_token *list)
 * @param list current list of token
 * @brief follow different rules to delete character in token before valid 
 */
void check_delete_end(struct list_token *list);
/**
 * @fn void check_delete(enum type_token type, struct list_token *list)
 * @brief check character to delete in the process
 */
void check_delete(enum type_token type, struct list_token *list);
/********************************************/


/*************** fct_lexer.c ****************/
/**
 * @fn struct token init_token(size_t i)
 * @param i current index in g_line
 * @brief initialize a struct token 
 * @return token initialized with char at index i in g_line and type WORD
 */
struct token init_token(size_t i);
/**
 * @fn int is_continue(struct token tok, size_t i)
 * @param i current index in g_line
 * @brief check if a token is delimited or not
 * @return 0 if token is delimited, 1 otherwise
 */
int is_continue(struct token tok, size_t i);
/**
 * @fn struct token new_token(struct token prev, size_t i)
 * @param i current index in g_line
 * @param prev previous token
 * @brief create a new token with the previous and the current
 * @return new token
 */
struct token new_token(struct token prev, size_t i);
/**
 * @fn struct list_token *init_list_token(size_t i)
 * @param i current index in g_line
 * @brief initialize a list_token
 * @return list_token initialized with next NULL and token with init_token
 */
struct list_token *init_list_token(size_t i);
/**
 * @fn struct list_token *take_1_token(size_t i)
 * @param i current index in g_line
 * @brief take the current token with call all functions
 * @return list with the good token
 */
struct list_token *take_1_token(size_t i);
/********************************************/
#endif
