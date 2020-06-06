#include "abstract_dict.h"
#include "ft_term.h"

int         execute_abstract_dict(t_op *ad, t_term *t)
{
    if (ad == NULL)
        return(true);
    if (ad->type & PARENTHESIS)
    {
        if (ad->next && (ad->next->type & PIPE || ad->next->type & RDG || ad->next->type & RG
            || ad->next->type & RDL|| ad->next->type & RL))
            ; // something to redirect the fd to pipe/filepath
        else if (ad->back && ad->back->type & PIPE)
            ; // take redirected fd
        execute_abstract_dict(ad->ch1, t); // take the result of that in a fd
    }
    if (ad->type & AND)
    {
        if (ad->ch1 == NULL)
            ; // last is pipe or redirection or paren
        if (ad->ch2 == NULL)
            ; // next is pipe or redirection or paren or and/or
        execute_and(ad, t);
    }
    else if (ad->type & OR)
    {
        f (ad->ch1 == NULL)
            ; // last is pipe or redirection or paren
        if (ad->ch2 == NULL)
            ; // next is pipe or redirection or paren or and/or
        execute_or(ad, t);
    }
    else if (ad->type & RDG || ad->type & RG
            || ad->type & RDL|| ad->type & RL)
    {
        if (ad->ch1 == NULL)
            ; // take redirection
        execute_redirection(ad, t);
    }
    else if (ad->type & PIPE)
    {
        if (ad->ch1 == NULL)
            ; // take redirection
        if (ad->ch2 == NULL)
            ; // redirect the fd
        execute_pipe(ad, t);
    }
    else
    {
        if (ad->ch1 == NULL)
            ; // something before semicolon or not operator
        if (ad->ch2 == NULL)
            ; // something after semicolon or not operator
        // if the are no null there are no operator (or only semicolon(s))
    } 
    return(execute_abstract_dict(ad->next, t));
}