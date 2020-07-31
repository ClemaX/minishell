#include "abstract_dict.h"

int         execute_redirections(t_op *ad, t_term *t)
{
    if (t->flags & TAKE_FD)
    {

        int     fd;

        if (ad->type & RG)
        {
            if ((fd = open(((t_token *)ad->ch2)->data, O_WRONLY | O_CREAT | O_TRUNC,
			        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			    return (-1);
		    (void)dup2(fd, t->fd[1]);
        }
        else if (ad->type & RL)
        {
            if ((fd = open(((t_token *)ad->ch2)->data, O_RDONLY)) < 0)
			    return (-1);
		    (void)dup2(fd, t->fd[1]);
        }
        else if (ad->type & RDG)
        {
            if ((fd = open(((t_token *)ad->ch2)->data, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
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
    else if (!(t->flags & GIVE_FD))
        (void)redirect_to_fd(ad, t); // have to check if i am in << and do stuff
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
    (void)dup2(p.fd[0], t->fd[0]);// no fcking idea if this ll work
	return (0);
}
