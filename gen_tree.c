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

void            set_children(t_btree *children, t_token *k, bool copy)
{
    if (copy && k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
        ft_strlcpy(children->data, k->data, ft_strlen(k->data));
    else if (k->next && k->next->type == T_AND)
        children->status |= S_INAND;
    else if (k->next && k->next->type == T_OR)
        children->status |= S_INOR;
    else if (k->next && k->next->type == T_SEM)
        children->status |= S_SEM;
    else if (k->next && k->next->type == T_PIPE)
        children->status |= S_PIPE;
    
}

void            set_redirection(t_token *k, t_btree *children)
{
    if (k->next && k->next->type == T_GRAT)
        children->status |= S_G;
    else if (k->next && k->next->type == T_DGRAT)
        children->status |= S_DG;
    else if (k->next && k->next->type == T_DLESS)
        children->status |= S_DL;
    else if (k->next && k->next->type == T_LESS)
        children->status |= S_L;
}

t_btree         *gen_cmd(t_token *k)
{
    t_btree     *children;

    if (!(children = malloc(sizeof(t_btree))))
        return (NULL);
    if (k->next && (k->next->type == T_GRAT || k->next->type == T_DGRAT ||
        k->next->type == T_LESS || k->next->type == T_DLESS))
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        set_redirection(k, children);
        children->ch2 = gen_cmd(k->next->next);
        children->ch1 = NULL;
    }
    else
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->ch1 = NULL;
        children->ch2 = NULL;
    }
    return (children);
}

t_btree         *gen_job(t_token *k)
{
    t_btree     *children;

    if (!(children = malloc(sizeof(t_btree))))
        return (NULL);
    if (k->next && (k->next->type == T_AND ||
            k->next->type == T_OR || k->next->type == T_SEM))
    {
        set_children(children, k, true);
        children->ch2 = gen_btree(k->next->next);
        children->ch1 = NULL;
    }
    else if (k->next && k->next->type == T_PIPE)
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->status |= S_PIPE;
        children->ch2 = gen_job(k->next->next);
        children->ch1 = NULL;
    }
    else
    {
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->ch1 = gen_cmd(k);
        children->ch2 = NULL;
    }
    return (children);
}

t_btree         *gen_btree(t_token *k)
{
    t_btree     *children;

    if (!(children = malloc(sizeof(t_btree))))
        return (NULL);
    children->status = 0;
    if (k->next && k->next->type == CLOSE_PAR)
    {
    children->ch2 = (k->next->next) ? gen_btree(k->next->next->next) : NULL;
        set_children(k->next, children, false);
        set_redirection(k->next, children);
        if (k->data && (children->data = malloc(sizeof(char) * ft_strlen(k->data)))) // catch error
            ft_strlcpy(children->data, k->data, ft_strlen(k->data));
        children->status |= S_OUTPAR;
        children->ch1 = NULL;
    }
    else if (k->type == OPEN_PAR)
    {
        children->status |= S_INPAR;
        children->ch2 = gen_btree(k->next);
        children->ch1 = NULL;
    }
    else if (k->next && (k->next->type == T_AND ||
            k->next->type == T_OR || k->next->type == T_SEM))
    {
        set_children(children, k, true);
        children->ch2 = gen_btree(k->next->next);
        children->ch1 = NULL;
    }
    else
    {
        children->ch1 = gen_job(k);
        children->ch2 = NULL;
    }
    return (children); // normally returns the first elem
}