#include "abstract_dict.h"

/* TO DO:
- redirection fcts
- simple cmd to execution fct
- semicolon in exe fct
- tokenize fct

DID:
- all builting
- store fd in parentheses
- pipe tale fd, pipe give fd
- global execution recursive loop
- redirection take fd, give fd
- exe and
- exe or
- redirections exe
- simple cmd exe
- basic pipe

NOTES:
- AND/OR could fail in very specific cases (idk really)
- un
*/

int         execute_abstract_dict(t_op *ad, t_term *t)
{
    if (ad == NULL)
        return(true);
    if (ad->type & PARENTHESIS)
    {
        if (ad->next && (ad->next->type & PIPE || ad->next->type & RDG || ad->next->type & RG
            || ad->next->type & RDL|| ad->next->type & RL))
            (void)give_fd(ad, t, 1);
        else if (ad->back && ad->back->type & PIPE)
            (void)take_fd(ad, t);
    }
    if (ad->type & AND)
        (void)execute_and(ad, t);
    else if (ad->type & OR)
        (void)execute_or(ad, t);
    else if (ad->type & RDG || ad->type & RG
            || ad->type & RDL|| ad->type & RL)
    {
        if (ad->ch1 == NULL)
            t->flags |= TAKE_FD;
        (void)execute_redirection(ad, t);
    }
    else if (ad->type & PIPE)
    {
        if (ad->ch1 == NULL)
            t->flags |= TAKE_FD;
        if (ad->ch2 == NULL)
            t->flags |= GIVE_FD;
        (void)execute_pipe(ad, t);
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