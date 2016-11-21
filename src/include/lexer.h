/**
 * @file lexer.h
 */

/**
 * @fn void init_lexer(char *s)
 * @param s String with all commands
 * @brief initialize struct of the lexer, specially g_list
 */
void init_lexer(char *s);
/**
 * @fn char *take_token(void)
 * @return current token
 */
char *take_token(void);
/**
 * @fn void valid_token(void)
 * @brief update g_list, pass to next
 */
void valid_token(void);
/**
 * @fn char *take_next_token(void)
 * @return next token
 */
char *take_next_token(void);
