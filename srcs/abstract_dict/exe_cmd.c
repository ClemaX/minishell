#include "abstract_dict.h"

int         builting_not_in_slash_bin(char *name, char **argv, t_term *t)
{
    if (!ft_strncmp(name, "echo", 5))
        return (ft_echo("ac", argv, "envp")); // false is true
    else if (!ft_strncmp(name, "cd", 3))
        return (ft_cd("ac", argv, t));
    else if (!ft_strncmp(name, "pwd", 4))
        return (ft_pwd());
    else if (!ft_strncmp(name, "export", 7))
        return (ft_export("ac", argv, t, "name"));
    else if (!ft_strncmp(name, "unset", 6))
        return (ft_unset(t, "name"));
    else if (!ft_strncmp(name, "env", 4))
        return (ft_env(t->env));
    else if (!ft_strncmp(name, "exit", 5))
        return (ft_exit());
    return (true);
}

int         execute_cmd(t_token *data, t_term *t)
{
    char    **argv;

    if (!(argv = token_tab(data)))
        return (-1);
    if (builting_not_in_slash_bin(argv[0], argv + 1, t) && !(t->pid = fork()))
    {
        t->st += execve(get_path(argv[0]), argv + 1, t->env);
        ft_printf("execve returned! errno is [%d]\n", argv[0]); // name or errno ?
		return (false);
    }
    else if (t->pid < 0)
        return (BASH_ERROR_CODE);
    while (waitpid(t->pid, NULL, 0) < 0)
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