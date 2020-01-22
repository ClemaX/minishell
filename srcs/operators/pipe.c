/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 05:05:50 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 12:08:35 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <parser.h>
#include <unistd.h>
#include <sys/wait.h>
#include <map.h>
#include <execution.h>

static int		ft_pipe_fill(char in, char out, int fd_read, int fd_write, t_node *node, t_map *env, char *name)
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
		if (node->type == NODE_R_IN)
			redirection(node->ch1, node->data, STDIN_FILENO, env, name);
		else if (node->type == NODE_R_OUT)
			redirection(node->ch1, node->data, STDOUT_FILENO, env, name);
		else if (node->type == NODE_CMD)
			simple_cmd(node, env, name, ft_execve);
	}
	while (wait(NULL) > 0)
		;
	return (pid);
}

static void	print_tree(t_node *btree)
{
	if (btree)
	{
		if (btree->type == NODE_CMD)
			ft_printf("[CMD]: %s\n", btree->data);
		else if (btree->type == NODE_ARG)
			ft_printf("[ARG]: %s\n", btree->data);
		else
			ft_printf("[%d]\n", btree->type);
		print_tree(btree->ch1);
		print_tree(btree->ch2);
	}
}

void		ft_pipe(t_node *node, t_map *env, char *name)
{
	int		fd_write;
	int		fd_read;
	int		pipe_fd[2];
	int		pid;
	t_node	*job;

	if (!node)
		return ;
	pipe(pipe_fd);
	fd_write = pipe_fd[1];
	fd_read = pipe_fd[0];
	pid = ft_pipe_fill(0, 1, 0, fd_write, node->ch1, env, name);
	job = node->ch2;
	while (job->ch2 && job->type == NODE_PIPE)
	{
		close(fd_write);
		pipe(pipe_fd);
		fd_write = pipe_fd[1];
		pid = ft_pipe_fill(1, 1, fd_read, fd_write, job->ch1, env, name);
		close(fd_read);
		fd_read = pipe_fd[0];
		job = job->ch2;
	}
	fd_read = pipe_fd[0];
	close(fd_write);
	pid = ft_pipe_fill(1, 0, fd_read, fd_write, job, env, name);
	close(fd_write);
	close(fd_read);
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