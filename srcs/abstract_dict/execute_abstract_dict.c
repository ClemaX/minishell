#include "abstract_dict.h"
#include "ft_term.h"


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


int         execute_redirections(t_op *ad, t_term *t)
{
    if (t->flags & TAKE_FD)
    {

        int     fd;

        if (ad->type & RG)
        {
            if ((fd = open(ad->ch2, O_WRONLY | O_CREAT | O_TRUNC,
			        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			    return (-1);
		    (void)dup2(fd, t->fd[1]);
        }
        else if (ad->type & RL)
        {
            if ((fd = open(ad->ch2, O_RDONLY)) < 0)
			    return (-1);
		    (void)dup2(fd, t->fd[1]);
        }
        else if (ad->type & RDG)
        {
            if ((fd = open(ad->ch2, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
		            S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			    return (-1);
		    (void)dup2(fd, t->fd[1]);
        }
        else
        {
        ; // weird shit
        }
        (void)close(fd);
        }
    else
        (void)redirect_to_fd(ad, t);
    return (true);
}

int         give_fd(t_op *ad, t_term *t, bool index)
{
    (void)pipe(t->fd);
    if (!(t->pid = fork()))
    {
        (void)dup2(t->fd[index], index);
        (void)execute_abstract_dict(ad->ch1, t);

    }
    else if (t->pid < 0)
        return (t->st = BASH_ERROR_CODE);
    while (wait(NULL) > 0)
        ;
    t->pid = 0;
    (void)close(t->fd[index]);
    return (true);
}

int         take_fd(t_op *ad, t_term *t)
{
    t_pipe  p;

    (void)pipe(p.fd);
    (void)dup2(p.fd[1], t->fd[1]);
    (void)give_fd(ad, t, 0);
    (void)dup2(p.fd[0], t->fd[0]);// no fcking idea if this would work
}

int         builting_not_in_slash_bin(char *name, char **argv, t_term *t)
{
    if (!ft_strncmp(name, "echo", 5))
        return (ft_echo()); // false is true
    else if (!ft_strncmp(name, "cd", 3))
        return (ft_cd());
    else if (!ft_strncmp(name, "pwd", 4))
        return (ft_pwd());
    else if (!ft_strncmp(name, "export", 7))
        return (ft_export());
    else if (!ft_strncmp(name, "unset", 6))
        return (ft_unset());
    else if (!ft_strncmp(name, "env", 4))
        return (ft_env());
    else if (!ft_strncmp(name, "exit", 5))
        return (ft_exit());
    return (true);
}

int         execute_cmd(char *data, t_term *t)
{
    char    **argv;

    if (!(argv = tokenize(data)))
        return (-1);
    if (builting_not_in_slash_bin(argv[0], argv + 1, t) && !(t->pid = fork()))
    {
        t->st += execve(get_path(argv[0]), argv + 1, t->env);
        ft_printf("execve returned! errno is [%d]\n", argv[0]); // name or errno ?
		return (false);
    }
    else if (t->pid < 0)
        return (BASH_ERROR_CODE);
    while (waitip(t->pid, NULL, 0) < 0)
        ;
    t->pid = 0;
    while (*argv)
        free((*argv)++);
    free(argv);
    return (true);
}

int         execute_and(t_op *ad, t_term *t)
{
    if (ad->ch1 == NULL && t->st)
        return (false);
    if (ad->ch1 && ad->ch2)
    {
        (void)execute_cmd(ad->ch1, t);
        if (t->st)
            return (false);
        (void)execute_cmd(ad->ch2, t);
    }
    return (true);
}

int         execute_or(t_op *ad, t_term *t)
{
    if (ad->ch1 == NULL && !t->st)
        return (false);
    if (ad->ch1 && ad->ch2)
    {
        (void)execute_cmd(ad->ch1, t);
        if (!t->st)
            return (false);
        (void)execute_cmd(ad->ch2, t);
    }
    return (true);
}

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