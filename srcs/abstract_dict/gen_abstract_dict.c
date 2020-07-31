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

    //token_list = token_list->next; // why i did that first ?
    if (!token_list || token_list->type & CLOSE_PAR || !(next = malloc(sizeof(t_op))))
        return (NULL);
    next->type = 0;
    next->back = curr;
    next->ch1 = NULL;
    next->ch2 = NULL;
    if (token_list->type & PARENTHESIS && (curr->type |= PARENTHESIS))
    {
        (void)gen_architecture(token_list->next, curr->ch1 = next);
        next = gen_architecture(token_list, NULL);
    }
    if (curr)
    {
        ((t_op *)curr)->next = next;
        ((t_op *)curr)->type |= token_list->type;
		ft_printf("[type in gen arch is %d]\n", curr->type);
    }
    return (gen_architecture(token_list->next, next));
}

// step 2
bool        gen_sub_architecture(t_token *token_list, t_op *curr)
{
    if (!token_list || !token_list->data || !curr->type)
	{
        return (false);
	}
		ft_printf("[op type sub arch is %d]\n", curr->type);
		ft_printf("[token data in sub arch is %s]\n", token_list->data);

    if (curr->type & AND || curr->type & OR)
    {
        if (curr->back && (curr->back->type & PIPE || curr->back->type & RDG || curr->back->type & RG
                || curr->back->type & RDL|| curr->back->type & RL || curr->back->type & PARENTHESIS))
            curr->ch1 = NULL;
        else
            curr->ch1 = token_next_cmd(&token_list);
        if (curr->next && (curr->next->type & PIPE || curr->next->type & RDG || curr->next->type & RG
                || curr->next->type & RDL|| curr->next->type & RL || curr->next->type & PARENTHESIS
                || curr->next->type & AND || curr->next->type & OR)) // if AND/OR after ch2 = NULL, next->ch1 = the value
            curr->ch2 = NULL;
        else
            curr->ch2 = token_next_cmd(&token_list);
		// tests 
		//if (curr->ch1)
		//	ft_printf("[test ch1: %s]\n", ((t_token *)curr->ch1)->data);
		//if (curr->ch2)
		//	ft_printf("[test ch2: %s]\n", ((t_token *)curr->ch2)->data);
		// end tests
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
		{
            (void)gen_sub_architecture(token_list, curr->ch1);
		}
		ft_printf("back [%p]\n", curr->back);
        if (!curr->back || (curr->back && curr->type & SEMICOLON))
            curr->ch1 = token_next_cmd(&token_list);
        else
            curr->ch1 = NULL;
        if (!curr->next->type) // can segfault
            curr->ch2 = token_next_cmd(&token_list);
        else
            curr->ch2 = NULL;
    }
		// tests 
	if (curr->ch1)
		ft_printf("[test ch1: %s]\n", ((t_token *)curr->ch1)->data);
	if (curr->ch2)
		ft_printf("[test ch2: %s]\n", ((t_token *)curr->ch2)->data);
		// end tests
    if (curr->next /*&& ((t_op *)curr->next)->type*/)
        return (gen_sub_architecture(token_list, curr->next));
    return (true);
}