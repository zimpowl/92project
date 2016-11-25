#ifndef AST_READER_H
#define AST_READER_H

/**
 * @file ast_reader.h
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//read_ast.c
/**
 * @fn int read_a(struct ntree *ntree)
 * @param  ntree
 * @return return the value
 */
int read_a(struct ntree *ntree);
/**
 * @fn int manage_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int manage_a(struct ntree *ntree);
/**
 * @fn int list_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int list_a(struct ntree *ntree);
/**
 * @fn int and_or_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int and_or_a(struct ntree *ntree);
/**
 * @fn int command_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int command_a(struct ntree *ntree);
/**
 * @fn int pipeline_nor_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int pipeline_nor_a(struct ntree *ntree);
/**
 * @fn int pipeline_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int pipeline_a(struct ntree *ntree);
/**
 * @fn char *var_assigned_a(char *name)
 * @param ntree
 * @return return the value.
 */
char *var_assigned_a(char *name);
/**
 * @fn int assign_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int check_assign_a(struct ntree *ntree);
/**
 * @fn int check_condition_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int check_condition_a(struct ntree *ntree);

//rules_ast.c
/**
 * @fn int rules_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int rules_a(struct ntree *ntree);
/**
 * @fn int rule_if_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int rule_if_a(struct ntree *ntree);
/**
 * @fn int rule_while_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int rule_while_a(struct ntree *ntree);
/**
 * @fn int rule_until_a(struct ntree *ntree)
 * @param ntree
 * @return return the value.
 */
int rule_for_a(struct ntree *ntree);
/**
 * @fn int rule_until_a(struct ntree *ntree);
 * @param ntree
 * @return return the value.
 */
int rule_until_a(struct ntree *ntree);
/**
 * @fn int reg_func_a(struct ntree *ntree);
 * @param ntree 
 * @return return the value.
 */
int reg_func_a(struct ntree *ntree);
/**
 * @fn int reg_func_a(struct ntree *ntree);
 * @param ntree 
 * @return return the value.
 */
int check_func_a(char *name);
/**
 * @fn int do_group_a(struct ntree *ntree)
 * @param ntree 
 * @return return the value.
 */
int rule_case_a(struct ntree *ntree);
/**
 * @fn int do_group_a(struct ntree *ntree)
 * @param ntree 
 * @return return the value.
 */
int rule_caseitem_a(struct ntree *ntree, char *str);
/**
 * @fn int do_group_a(struct ntree *ntree)
 * @param ntree 
 * @return return the value.
 */
int do_group_a(struct ntree *ntree);

#endif
