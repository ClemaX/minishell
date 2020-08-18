#include <ft_term.h>
#include <abstract_dict.h>

static int  open_fd(char *name, short std)
{
    int     fd;

    if (std & RG)
    {
        if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC,
			    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
		(void)dup2(fd, STDOUT_FILENO);
    }
    else if (std & RL)
    {
        if ((fd = open(name, O_RDONLY)) < 0)
			return (-1);
		(void)dup2(fd, STDIN_FILENO);
    }
    else if (std & RDG)
        {
        if ((fd = open(name, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
		        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
		(void)dup2(fd, STDOUT_FILENO);
        }
    else
    {
        ; // weird shit
    }
    (void)close(fd);
    return (true);
}

int         redirect_to_fd(t_op *ad, t_term *t)
{
    char	**argv;
	int		ac;


    if (!(argv = token_tab(ad->ch1, &ac)))
        return (-1);
    if (!(t->pid = fork()))
    {
		ft_printf("Redirection forks and don't wait correctly the fork\n");
        //(void)dup(STDOUT_FILENO);
        if (open_fd(((t_token *)ad->ch2)->data, ad->type) < 0)
            return (-1);
        if (!builtin(ac, argv, t))
        {
            // TODO: t->st += execve(get_path(argv[0]), argv + 1, t->env);
            ft_printf("execve returned! errno is [%s]\n", argv[0]); // name or errno ?
		    return (true);
        }
    }
    else if (t->pid < 0)
	{
        return (t->st = BASH_ERROR_CODE);
	}
	while (waitpid(t->pid, NULL, 0) <= 0)
        ;
    t->pid = 0;
    free(argv);
    return (true);
}
