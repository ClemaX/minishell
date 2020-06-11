#ifndef ABSTRACT_DICT_H
# define ABSTRACT_DICT_H

#include "operators.h"
#include "builtins.h"
#include "lexer.h"

t_op        *gen_architecture(int **token_list, t_op *curr);
bool        gen_sub_architecture(char **token_list, t_op *curr);
int         execute_abstract_dict(t_op *ad, t_term *t);

#endif