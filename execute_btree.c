#include "btree.h"
#include "lexer.h"
#include "ft_term.h"

bool        execute_job(t_token *bt, t_term *t)
{
    if (bt->type & S_PIPE)
        execute_pipe(bt, t);
    else if (bt->type & NONE)
        ; // execve
    else
        exucute_redirection(bt, t);
}

bool        execute_btree(t_token *bt, t_term *t)
{
    if (bt == NULL)
        return (true);
    if (bt->type & S_INAND)
        ;
    else if (bt->type & S_INOR)
        ;
    else if (bt->type & S_SEM)
        ;
    else if (bt->type & OPEN_PAR)
        ;
    else if (bt->type & CLOSE_PAR)
        ;
    else
        execute_job(bt, t);
    return (execute_btree(bt->next, t));
}