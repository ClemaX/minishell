#include "abstract_dict.h"
#include "ft_term.h"

static int  fill(int ac, const char **argv, t_pipe p, t_term *t)
{
    if (!(t->pid = fork()))
    {
        (void)dup(STDOUT_FILENO);
        if (p.in)
            (void)dup2(p.r, STDIN_FILENO);
        if (p.out)
            (void)dup2(p.w, STDOUT_FILENO);
        else
        {
            if (builting_not_in_slash_bin(ac, argv, t))
            {
                // TODO: t->st += execve(get_path(argv, t->env);
                ft_printf("execve returned! errno is [%s]\n", argv[0]); // name or errno ?
		        return (true);
            }
        }
        // remember to remove the flags in a specific (not alreaddy specified) momment
    }
    else if (t->pid < 0)
        return (t->st = BASH_ERROR_CODE);
    while (wait(NULL) > 0)
        ;
    t->pid = 0;
    // pu to zero the fd in t_pipe
    return (true);
}

int         execute_pipe(t_op *ad, t_term *t)
{
    t_pipe		p;
    const char	**argv;
    int			ac;

    (void)pipe(p.fd);
    if (!(argv = token_tab(ad->ch1, &ac)))
        return (-1);
    if (!ad->ch1) // take fd
        (void)dup2(p.fd[0], t->fd[1]); // fd write ? sure ?
    p.r = p.fd[0];
    p.w = p.fd[1];
    p.in = 0;
    p.out = ad->ch1 ? 0 : 1;
    (void)fill(ac, argv, p, t);
    free(argv);
    if (!(argv = token_tab(ad->ch2, &ac)))
        return (-1);
    p.r = p.fd[0];
    (void)close(p.w);
    p.in = ad->ch2 ? 0: 1;
    p.out = 0;
    (void)fill(ac, argv, p, t);
    if (!ad->ch2) // give fd
        (void)dup2(t->fd[1], p.fd[0]); // probally bad but could be good
    (void)close(p.r);
    (void)close(p.w);
    free(argv);
    return (true);
}