#ifndef PARSER_H
#define PARSER_H

/**
 * @file parser.h
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

//input_parser.c
/**
 * @fn struct ntree *input_p(void)
 * @return return the new tree
 */
struct ntree *input_p(void);
//list_parser.c
/**
 * @fn struct ntree *list_p(void)
 * @return return the new tree
 */
struct ntree *list_p(void);
/**
 * @fn struct ntree *compound_list_p(void)
 * @return return the new tree
 */
struct ntree *compound_list_p(void);
/**
 * @fn struct ntree *do_group_p(void)
 * @return return the new tree
 */
struct ntree *do_group_p(void);
//and_or_parser.c
/**
 * @fn struct ntree *and_or_p(void)
 * @return return the new tree
 */
struct ntree *and_or_p(void);
//pipeline_parser.c
/**
 * @fn struct ntree *pipeline_p(void)
 * @return return the new tree
 */
struct ntree *pipeline_p(void);
/**
 * @fn struct ntree *pipeline_bis_p(struct ntree *ntree)
 * @return return the new tree
 */
struct ntree *pipeline_bis_p(struct ntree *ntree);
//command_parser.c
/**
 * @fn struct ntree *command_p(void)
 * @return return the new tree
 */
struct ntree *command_p(void);
/**
 * @fn struct ntree *simple_command_p(void)
 * @return return the new tree
 */
struct ntree *simple_command_p(void);
/**
 * @fn struct ntree *prefix_p(void)
 * @return return the new tree
 */
struct ntree *prefix_p(void);
/**
 * @fn struct ntree *element_p(void)
 * @return return the new tree
 */
struct ntree *element_p(void);
//shellcom_parser.c
/**
 * @fn struct ntree *shell_command_p(void)
 * @return return the new tree
 */
struct ntree *shell_command_p(void);
/**
 * @fn struct ntree *shell_commandbis_p(void)
 * @return return the new tree
 */
struct ntree *shell_commandbis_p(void);
//rules_parser.c
/**
 * @fn struct ntree *rule_if_p(void)
 * @return return the new tree
 */
struct ntree *rule_if_p(void);
/**
 * @fn struct ntree *rule_if_p(void)
 * @return return the new tree
 */
struct ntree *rule_else_p(void);
/**
 * @fn struct ntree *rule_if_p(void)
 * @return return the new tree
 */
struct ntree *rule_elseclause_p(void);
/**
 * @fn struct ntree *rule_ifbis_p(struct ntree *ntree)
 * @return return the new tree
 */
struct ntree *rule_fi_p(struct ntree *ntree);
/**
 * @fn struct ntree *rule_whiletil_p(void)
 * @return return the new tree
 */
struct ntree *rule_whiletil_p(void);
/**
 * @fn struct ntree *rule_for_p(void);
 * @return return the new tree
 */
struct ntree *rule_for_p(void);
/**
 * @fn struct ntree *rule_forin_p(struct ntree *ntree);
 * @return return the new tree
 */
struct ntree *rule_forin_p(struct ntree *ntree);
//func_parser.c
/**
 * @fn struct ntree *func_p(void)
 * @return return the new tree
 */
struct ntree *func_p(void);
/**
 * @fn void func_bis_p(void)
 * @return return the new tree
 */
void func_bis_p(void);
/**
 * @fn struct ntree *func_bisbis_p(struct ntree *ntree)
 * @return return the new tree
 */
struct ntree *func_bisbis_p(struct ntree *ntree);
/**
 * @fn struct ntree *rule_case_p();
 * @param ntree 
 * @return return the value.
 */
struct ntree *rule_case_p();
/**
 * @fn struct ntree *rule_case_p();
 * @param ntree 
 * @return return the value.
 */
struct ntree *rule_caseclause_p(struct ntree *ntree);
/**
 * @fn struct ntree *rule_case_p();
 * @param ntree 
 * @return return the value.
 */
struct ntree *rule_caseitem_p();
//redir_parser.c
/**
 * @fn struct ntree *redir_p(void)
 * @return return the new tree
 */
struct ntree *redir_p(void);
/**
 * @fn int check_redir(char *tok)
 * @return return the new tree
 */
int check_redir(char *tok);
/**
 * @fn int check_ionumber(char *tok)
 * @return return the new tree
 */
int check_ionumber(char *tok);

//useful everywhere in input_parser.c
/**
 * @fn int skip_line();
 * @return return int
 */
int skip_line();
/**
 * @fn int check_token_reserved(void)
 * @return return int
 */
int check_operators_p(void);
/**
 * @fn int check_token_reserved(void)
 * @return return int
 */
int check_reserved_p(void);
#endif
