/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 05:05:50 by chamada           #+#    #+#             */
/*   Updated: 2020/01/23 19:31:24 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "unistd.h"
#include <sys/wait.h>
#include <map.h>
#include <execution.h>
#include <global_var.h>

static int	ft_pipe_fill(char in, char out, int fd_read, int fd_write, t_node *node, t_map *env, char *name)
{
	int		stdout;
	int		ret;

	if (!(g_pid = fork()))
	{
		// restore_sigin_child() see if i have to do
		stdout = dup(STDOUT_FILENO);
		if (in)
			dup2(fd_read, STDIN_FILENO);
		if (out)
			dup2(fd_write, STDOUT_FILENO);
		if (node->type == NODE_R_IN)
			ret = redirection(node->ch1, node->data, STDIN_FILENO, env, name);
		else if (node->type == NODE_R_OUT)
			ret = redirection(node->ch1, node->data, STDOUT_FILENO, env, name);
		else if (node->type == NODE_CMD)
			ret = simple_cmd(node, env, name, ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (wait(NULL) > 0)
		;
	g_pid = 0;
	return (ret);
}

int		ft_pipe(t_node *node, t_map *env, char *name)
{
	int		fd_write;
	int		fd_read;
	int		pipe_fd[2];
	t_node	*job;
	int		ret;

	if (!node)
		return (-1);
	pipe(pipe_fd);
	fd_write = pipe_fd[1];
	fd_read = pipe_fd[0];
	ret = ft_pipe_fill(0, 1, 0, fd_write, node->ch1, env, name);
	job = node->ch2;
	while (job->ch2 && job->type == NODE_PIPE)
	{
		close(fd_write);
		pipe(pipe_fd);
		fd_write = pipe_fd[1];
		ret += ft_pipe_fill(1, 1, fd_read, fd_write, job->ch1, env, name);
		close(fd_read);
		fd_read = pipe_fd[0];
		job = job->ch2;
	}
	fd_read = pipe_fd[0];
	close(fd_write);
	ret += ft_pipe_fill(1, 0, fd_read, fd_write, job, env, name);
	close(fd_write);
	close(fd_read);
	return (ret > 0 && ret < 42 ? 1 : ret); /* dont already know if a builtin can return 127 */
}

/*
#define READ 0
#define WRITE 1

void		ft_pipe(t_node *node, t_map *env, char *name)
{
	int		pipe_fd[2];
	int		fd[2];
	pid_t	pid;
	t_node	*job;

	if (!node || pipe(pipe_fd) == -1)
		return ;
	fd[0] = pipe_fd[0];
	fd[1] = pipe_fd[1];
	if (!(pid = fork()))
	{
//		dup2(fd[READ], STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[READ]);
		close(fd[WRITE]);
		simple_cmd(node->ch1, env, name, ft_execve);
		return ;
	}
	else if (pid < 0)
		return ;
	pipe(pipe_fd);
	if (!(pid = fork()))
	{
		fd[WRITE] = pipe_fd[WRITE];
		dup2(fd[READ], STDIN_FILENO);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		close(fd[READ]);
		close(pipe_fd[WRITE]);
		close(pipe_fd[READ]);
		simple_cmd(node->ch2, env, name, ft_execve);
		return ;
	}
	else if (pid < 0)
		return ;
	if (!(pid = fork()))
	{
		dup2(pipe_fd[READ], STDIN_FILENO);
//		dup2(fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		close(fd[READ]);
		close(fd[WRITE]);
		simple_cmd(node->ch2->ch2, env, name, ft_execve);
		return ;
	}
	else if (pid < 0)
		return ;
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	close(fd[READ]);
	close(fd[WRITE]);
	while ((wait(NULL) > 0))
		;
}*/



/* 1) fork()
	2) path
	3) exectution
	4) path
	fork()
	5) execution
	6) path
	fork ()
	7) execution
	8 ) pathq
	*/