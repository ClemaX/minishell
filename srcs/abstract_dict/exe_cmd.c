#include "abstract_dict.h"

int         builting_not_in_slash_bin(int ac, const char **argv, t_term *t)
{
    const char *name = argv[0];

    if (!ft_strncmp(name, "echo", 5))
        return (ft_echo(ac, argv)); // false is true
    else if (!ft_strncmp(name, "cd", 3))
        return (ft_cd(ac, argv, t));
    else if (!ft_strncmp(name, "pwd", 4))
        return (ft_pwd());
    else if (!ft_strncmp(name, "export", 7))
        return (ft_export(ac, argv, t));
    else if (!ft_strncmp(name, "unset", 6))
        return (ft_unset(ac, argv, t));
    else if (!ft_strncmp(name, "env", 4))
        return (ft_env(t->env));
    else if (!ft_strncmp(name, "exit", 5))
        return (ft_exit());
    return (true);
}

int         execute_cmd(t_token *data, t_term *t)
{
    const char	**argv;
	int			ac;

    if (!(argv = token_tab(data, &ac)))
        return (-1);
    if (builting_not_in_slash_bin(ac, argv, t) && !(t->pid = fork()))
    {
        // TODO: t->st += execve(get_path(argv, t->env));
        ft_printf("execve returned! name is [%s]\n", argv[0]); // name or errno ?
		return (false);
    }
    else if (t->pid < 0)
        return (BASH_ERROR_CODE);
    while (waitpid(t->pid, NULL, 0) < 0)
        ;
    t->pid = 0;
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