#ifndef ABSTRACT_DICT_H
# define ABSTRACT_DICT_H

#include "operators.h"
#include "builtins.h"
#include "lexer.h"
#include "sys/wait.h"

t_op	*gen_architecture(t_token *token_list, t_op *curr);
bool	gen_sub_architecture(t_token *token_list, t_op *curr);
int		execute_abstract_dict(t_op *ad, t_term *t);
void    *free_abstract_dict(t_op *ad);


int		builting_not_in_slash_bin(int ac, const char **argv, t_term *t);
int		execute_cmd(t_token *data, t_term *t);
int		execute_and(t_op *ad, t_term *t);
int		execute_or(t_op *ad, t_term *t);

int		execute_redirections(t_op *ad, t_term *t);
int		give_fd(t_op *ad, t_term *t, bool index);
int		take_fd(t_op *ad, t_term *t);

const char	*get_path(const char *name);

#endif
