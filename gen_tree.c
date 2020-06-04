#include "btree.h"
#include "lexer.h"
#include "stdio.h"

/*
Thinked to solve:
echo a | echo b && (echo c || echo d)
echo a | echo b && (echo c || echo d) && (echo e)
echo a && (((echo b) && echo c) && echo d) && echo e
(echo a && echo b) > c
(echo a && echo b) | echo d
*/

void            set_children(t_token *children, t_token *k, bool copy)
{
    if (copy && k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
        ft_strlcpy(children->data, k->data, ft_strlen(k->data));
    else if (k->next && k->next->type == T_AND)
        children->type |= S_INAND;
    else if (k->next && k->next->type == T_OR)
        children->type |= S_INOR;
    else if (k->next && k->next->type == T_SEM)
        children->type |= S_SEM;
    else if (k->next && k->next->type == T_PIPE)
        children->type |= S_PIPE;
    
}

void            set_redirection(t_token *k, t_token *children)
{
    if (k->next && k->next->type == T_GRAT)
        children->type |= S_G;
    else if (k->next && k->next->type == T_DGRAT)
        children->type |= S_DG;
    else if (k->next && k->next->type == T_DLESS)
        children->type |= S_DL;
    else if (k->next && k->next->type == T_LESS)
        children->type |= S_L;
}

t_token         *gen_cmd(t_token *k)
{
    t_token     *children;

    if (!(children = malloc(sizeof(t_token))))
        return (NULL);
    if (k->next && (k->next->type == T_GRAT || k->next->type == T_DGRAT ||
        k->next->type == T_LESS || k->next->type == T_DLESS))
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        set_redirection(k, children);
        children->next = gen_cmd(k->next->next);
    }
    else
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->type = NONE;
        children->next = NULL;
    }
    return (children);
}

t_token         *gen_job(t_token *k)
{
    t_token     *children;

    if (!(children = malloc(sizeof(t_token))))
        return (NULL);
    if (k->next && (k->next->type == T_AND ||
            k->next->type == T_OR || k->next->type == T_SEM))
    {
        set_children(children, k, true);
        children->next = gen_btree(k->next->next);
    }
    else if (k->next && k->next->type == T_PIPE)
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->type |= S_PIPE;
        children->next = gen_job(k->next->next);
    }
    else
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->next = gen_cmd(k);
    }
    return (children);
}

t_token         *gen_btree(t_token *k)
{
    t_token     *children;

    if (!(children = malloc(sizeof(t_token))))
        return (NULL);
    children->type = 0;
    if (k->next && k->next->type == CLOSE_PAR)
    {
    children->next = (k->next->next) ? gen_btree(k->next->next->next) : NULL;
        set_children(k->next, children, false);
        set_redirection(k->next, children);
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->type |= S_OUTPAR;
    }
    else if (k->type == OPEN_PAR)
    {
        children->type |= S_INPAR;
        children->next = gen_btree(k->next);
    }
    else if (k->next && (k->next->type == T_AND ||
            k->next->type == T_OR || k->next->type == T_SEM))
    {
        set_children(children, k, true);
        children->next = gen_btree(k->next->next);
    }
    else
        children->next = gen_job(k);
    return (children); // normally returns the first elem
}