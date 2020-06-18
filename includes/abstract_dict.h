#ifndef ABSTRACT_DICT_H
# define ABSTRACT_DICT_H

#include "operators.h"
#include "builtins.h"
#include "lexer.h"
#include "sys/wait.h"

t_op        *gen_architecture(t_token *token_list, t_op *curr);
bool        gen_sub_architecture(t_token *token_list, t_op *curr);
int         execute_abstract_dict(t_op *ad, t_term *t);

int         builting_not_in_slash_bin(char *name, char **argv, t_term *t);
int         execute_cmd(t_token *data, t_term *t);
int         execute_and(t_op *ad, t_term *t);
int         execute_or(t_op *ad, t_term *t);

int         execute_redirections(t_op *ad, t_term *t);
int         give_fd(t_op *ad, t_term *t, bool index);
int         take_fd(t_op *ad, t_term *t);

#endif