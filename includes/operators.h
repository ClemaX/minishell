#ifndef OPERATORS_H
# define OPERATORS_H

#include "ft_term.h"

#define AND             1
#define OR              2
#define PIPE            4
#define RDG             8
#define RG              16
#define RDL             32
#define RL              64
#define PARENTHESIS     128
#define CLOSE_PAR       256
#define NONE            512
#define SEMICOLON       1024

typedef struct          s_operator
{
    void                *ch1;
    void                *ch2;
    struct s_operator   *next;
    struct s_operator   *back;
    short               type;
}                       t_op;

int                     redirect_to_fd(t_op *ad, t_term *t);
int                     execute_pipe(t_op *ad, t_term *t);

#endif