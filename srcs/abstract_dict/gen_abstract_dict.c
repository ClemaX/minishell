#include "abstract_dict.h"

// step 1) Create a linked list with all the operators <*list_symb_tokens[]> ("&& || | > < >> << ; ()") in order ,managing *next and *back ended by NULL
// step 2) Have fill ch1 and ch2 using <*list_text_tokens[]> with some rules:
    // - redirection and pipes has priority, i mean they always have to have an text token in ch1 and ch2
    // - redirection and pipes has an exeption: they could have an operator object (&& || | > < >> << ;) in ch1 or ch2.
        // to raise this exception redirection must have in ch1 some parentheses, for pipes parethesis could be in both
    // - redirections could have a pipe before (is like if here are parenthesis arond the pipe)
    // - for practical reasons, if && or || has an after or before a operator object the correspondent ch (ch1 or ch2) will
        // be NULL and the conecxion will be done by the next (not woks in back or only AND/OR yes for the others)
    // ch2 of redirection is always a text token
    // parentheses recursively create another step1 and then step 
    // semicolon has no ch1 or ch2 if there are conditions around

// step 1
t_op        *gen_architecture(t_token *token_list, t_op *curr)
{
    t_op    *next;

    token_list = token_list->next; // why i did that first ?
    if ((token_list || token_list->type & CLOSE_PAR) && !(next = malloc(sizeof(t_op))))
        return (NULL);
    next->type = 0;
    next->back = curr;
    next->ch1 = NULL;
    next->ch2 = NULL;
    if (token_list->type & T_OPEN_PAR && (curr->type |= PARENTHESIS))
    {
        (void)gen_architecture(token_list, curr->ch1 = next);
        next = gen_architecture(token_list, NULL);
    }
    if (curr)
    {
        ((t_op *)curr)->next = next;
        ((t_op *)curr)->type |= token_list->type;
    }
    return (gen_architecture(token_list, next));
}

// step 2
bool        gen_sub_architecture(t_token *token_list, t_op *curr)
{
    if (!token_list || !token_list->data || !curr)
        return (false);
    if (curr->type & AND || curr->type & OR)
    {
        if ((curr->back && (curr->back->type & PIPE || curr->back->type & RDG || curr->back->type & RG
                || curr->back->type & RDL|| curr->back->type & RL)) || curr->back->type & PARENTHESIS)
            curr->ch1 = NULL;
        else
            curr->ch1 = token_next_cmd(&token_list);
        if (curr->next && (curr->next->type & PIPE || curr->next->type & RDG || curr->next->type & RG
                || curr->next->type & RDL|| curr->next->type & RL || curr->next->type & PARENTHESIS
                || curr->next->type & AND || curr->next->type & OR)) // if AND/OR after ch2 = NULL, next->ch1 = the value
            curr->ch2 = NULL;
        else
            curr->ch2 = token_next_cmd(&token_list);
    }
    else if (curr->type & PIPE)
    {
        if (curr->back && curr->back->type & PARENTHESIS)
            curr->ch1 = NULL;
        else
            curr->ch1 = token_next_cmd(&token_list);
        if (curr->next && (curr->next->type & PARENTHESIS || curr->next->type & PIPE))
            curr->ch2 = NULL;
        else
            curr->ch2 = token_next_cmd(&token_list);
    }
    else if (curr->type & RDG || curr->type & RG
            || curr->type & RDL|| curr->type & RL)
    {
        if (curr->back && (curr->back->type & PARENTHESIS ||
                curr->back->type & PIPE))
            curr->ch1 = NULL;
        else
            curr->ch1 = token_next_cmd(&token_list);
        if (curr->next && curr->next->type & RDL)
            curr->ch2 = NULL;
        else
            curr->ch2 = token_next_cmd(&token_list);
    }
    else
    {
        if (curr->type & PARENTHESIS)
            (void)gen_sub_architecture(token_list, curr->ch1);
        if (!curr->back)
            curr->ch1 = token_next_cmd(&token_list);
        else
            curr->ch1 = NULL;
        if (!curr->next)
            curr->ch2 = token_next_cmd(&token_list);
        else
            curr->ch2 = NULL;
    }
    if (curr->next)
        return (gen_sub_architecture(token_list, curr->next));
    return (true);
}