/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 05:05:50 by chamada           #+#    #+#             */
/*   Updated: 2020/01/19 01:05:31 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "unistd.h"

static void		ft_pipe_fill(char in, char out, int fd_read, int fd_write)
{
	// execute our and systhem built-ins
	int		pid;
	int		stdout;

	if (!(pid = fork()))
	{
		// restore_sigin_child() see if i have to do
		stdout = dup(STDOUT_FILENO); /*see if i need this too */
		if (in)
			dup2(fd_read, STDIN_FILENO);
		if (out)
			dup2(fd_write, STDOUT_FILENO);
		// use of execvp
		/*
		!made_in_42(prcss1->av[0])
		? execve(path_get(prcss1->glob_env, prcss1->av[0]),
		prcss1->av, map_export(prcss1->glob_env))
		: find_built_in(prcss1->av[0], prcss1, av);

		---> traduction of this code with our new struct <---
		*/ 

	}
	else if (pid < 0)
		return ;
	while (waitpid(pid, NULL, 0) < 0)
		;
	return ;
}

void		ft_pipe(t_node *node)
{
	int		fd_write;
	int		fd_read;
	int		pipe_fd[2];
	t_node	*job;

	if (!node)
		return ;
	pipe(pipe_fd);
	fd_write = pipe_fd[1];
	fd_read = pipe_fd[0];
	ft_pipe_fill(0, 1, 0, fd_write);
	job = node->ch2;
	while (job && job->type == "our node pipe")
	{
		close(fd_write);
		pipe(pipe_fd);
		fd_write = pipe_fd[1];
		ft_pipe_fill(1, 1, fd_read, fd_write);
		close(fd_read);
		fd_read = pipe_fd[0];
		job = job->ch2;
	}
	fd_read = pipe_fd[0];
	close(fd_write);
	ft_pipe_fill(1, 0, fd_read, fd_write);
	close(fd_read);
}
