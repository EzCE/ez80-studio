/**
 * --------------------------------------
 * 
 * eZ80 Studio Source Code - parser.h
 * By RoccoLox Programs and TIny_Hacker
 * Copyright 2022 - 2025
 * License: GPL-3.0
 * 
 * --------------------------------------
**/

/**
 * @brief Parse bitwise OR.
 * 
 * @return long Parsing result.
 */
long parser_BR(void);

/**
 * @brief Parse bitwise XOR.
 * 
 * @return long Parsing result.
 */
long parser_BX(void);

/**
 * @brief Parse bitwise AND.
 * 
 * @return long Parsing result.
 */
long parser_BA(void);

/**
 * @brief Parse left / right bitshift.
 * 
 * @return long Parsing result.
 */
long parser_S(void);

/**
 * @brief Parse expression.
 * 
 * @return long Parsing result.
 */
long parser_E(void);

/**
 * @brief Parse term.
 * 
 * @return long Parsing result.
 */
long parser_T(void);

/**
 * @brief Parse factor.
 * 
 * @return long Parsing result.
 */
long parser_F(void);

/**
 * @brief Evalute a string containing a mathematical expression.
 * 
 * @param input String to evaluate.
 * @param error Address to store error code at.
 * @return unsigned long Result of evaluation.
 */
unsigned long parser_Eval(char *input, uint8_t *error);
