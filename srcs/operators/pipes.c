#include "abstract_dict.h"
#include "ft_term.h"

static int  fill(int ac, char **argv, t_pipe *p, t_term *t)
{
	(void)argv;
	(void)ac;
	(void)t;
    if (!(t->pid = fork()))
    {
		dup(STDOUT_FILENO);
		if (p->in)
			dup2(p->fd_read, STDIN_FILENO);
		if (p->out)
			dup2(p->fd_write, STDOUT_FILENO);
		if (builting_not_in_slash_bin(ac, argv, t))
    	{
        	// TODO: t->st += execve(get_path(argv, t->env);
        	ft_printf("execve returned! errno is [%s]\n", argv[0]); // name or errno ?
			return (true);
    	}
    }
    else if (t->pid < 0)
	{
        return (t->st = BASH_ERROR_CODE);
	}
	while (wait(NULL) > 0)
		;
	t->pid = 0;
	ft_bzero(p, sizeof(2));
    return (true);
}

int         execute_pipe(t_op *ad, t_term *t)
{
    t_pipe		p;
    char		**argv;
    int			ac;

	ft_printf("PIPE EXECUTION\n");
	if (!(argv = token_tab(ad->ch1, &ac)))
        return (-1);
    (void)pipe(p.fd);
	p.fd_write = p.fd[1];
	p.fd_read = p.fd[0];
    //if (!ad->ch1) // take fd
    //    (void)dup2(p.fd[0], t->fd[1]); // fd write ? sure ?

    //p.out = ad->ch1 ? 0 : 1;
	p.in = 0;
	p.out = 1;
    (void)fill(ac, argv, &p, t);
	free(argv);
    if (!(argv = token_tab(ad->ch2, &ac)))
	{
        return (-1);
	}
	p.in = 1;
	p.out = 0;
	p.fd_read = p.fd[0];
	close(p.fd_write);
	fill(ac, argv, &p, t);

	close(p.fd_write);
	close(p.fd_read);
	// before fill
    //p.in = ad->ch2 ? 0: 1;
    //if (!ad->ch2) // give fd
    //    (void)dup2(t->fd[1], p.fd[0]); // probally bad but could be good
    free(argv);
    t->pid = 0;

    return (true);
}
