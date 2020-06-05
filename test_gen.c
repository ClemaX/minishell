#include "lexer.h"

#define AND     1
#define OR      2
#define PIPE    4
#define RDG     8
#define RG      16
#define RDL     32
#define RL      64
#define PARENTHESIS 128

typedef struct s_operator
{
    void        *ch1;
    void        *ch2;
    struct s_operator  *next;
    struct s_operator  *back;
    short       type;
}               t_op;

char *list_symb_tokens[] = {};
char *list_text_tokens[] = {};

// step 1) Create a linked list with all the operators <*list_symb_tokens[]> ("&& || | > < >> << ; ()") in order ,managing *next and *back ended by NULL
// step 2) Have fill ch1 and ch2 using <*list_text_tokens[]> with some rules:
    // - redirection and pipes has priority, i mean they always have to have an text token in ch1 and ch2
    // - redirection and pipes has an exeption: they could have an operator object (&& || | > < >> << ;) in ch1 or ch2.
        // to raise this exception redirection must have in ch1 some parentheses, for pipes parethesis could be in both
    // - redirections could have a pipe before (is like if here are parenthesis arond the pipe)
    // - for practical reasons, if && or || has an after or before a operator object the correspondent ch (ch1 or ch2) will
        // be NULL and the conecxion will be done by the next (not woks in back or only AND/OR yes for the others)
    // ch2 of redirection is always a text token
    // parenthesis can be ignored if they are rounded by or and, they are only usseful for pipe and redirection
    // semicolon has no ch1 or ch2 if there are conditions around

// step 1
// take the int list like i did in my printf
t_op        *gen_architecture(int *token_list, t_op *last)
{
    t_op    *new;

    if (!(new = malloc(sizeof(t_op))))
        return (NULL);
    new->type = 0;
    if (last)
    {
        new->back = last;
        last->next = new;
    }
    else
        new->back = NULL;
    new->type |= *token_list;
    if (token_list + 1)
        token_list++;
    else
        return (new);
    gen_architecture(token_list, new);
}

// step 2
bool        gen_sub_architecture(char **token_list, t_op *curr)
{
    if (*token_list == NULL)
        return (false);
    if (curr->type & AND || curr->type & OR)
    {
        if (curr->back && (curr->back->type & PIPE || curr->back->type & RDG || curr->back->type & RG
                || curr->back->type & RDL|| curr->back->type & RL) || curr->back->type & PARENTHESIS)
            curr->ch1 = NULL;
        else // begin
        {
            curr->ch1 = ft_strdup(*token_list);
            *token_list = *token_list + 1? *token_list + 1 : NULL;
        }
        if (curr->next && (curr->next->type & PIPE || curr->next->type & RDG || curr->next->type & RG
                || curr->next->type & RDL|| curr->next->type & RL || curr->next->type & PARENTHESIS
                || curr->next->type & AND || curr->next->type & OR)) // if AND/OR after ch2 = NULL, next->ch1 = the value
            curr->ch2 = NULL;
        else // end
        {
            curr->ch2 = ft_strdup(*token_list);
            *token_list = *token_list + 1? *token_list + 1 : NULL;
        }
    }
    else if (curr->type & PIPE)
    {
        if (curr->back && (curr->back->type & PIPE || curr->back->type & PARENTHESIS))
            curr->ch1 = NULL;
        else
        {
            curr->ch1 = ft_strdup(*token_list);
            *token_list = *token_list + 1? *token_list + 1 : NULL;
        }
        if (curr->next && curr->next->type & PARENTHESIS)
            curr->ch2 = NULL;
        else
        {
            curr->ch2 = ft_strdup(*token_list);
            *token_list = *token_list + 1? *token_list + 1 : NULL;
        }
    }
    else if (curr->type & RDG || curr->type & RG
            || curr->type & RDL|| curr->type & RL)
    {
        if (curr->back && (curr->back->type & PARENTHESIS ||
                curr->back->type & PIPE))
            curr->ch1 = NULL; // that means ch1 is now back (the result of the pipe or the parenthesis
        else
        {
            curr->ch1 = ft_strdup(*token_list);
            *token_list = *token_list + 1? *token_list + 1 : NULL;
        }
        curr->ch2 = ft_strdup(*token_list);
        *token_list = *token_list + 1? *token_list + 1 : NULL;
    }
    else
    {
        ; // semicolon and parentesis (parentesis have to be removed)
    }
    if (curr->next)
        return (gen_sub_architecture(token_list, curr->next));
    return (true);
}