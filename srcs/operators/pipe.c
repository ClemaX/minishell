/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 05:05:50 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 05:34:14 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parser.h"
#include "unistd.h"
#include <sys/wait.h>
#include <map.h>
#include <execution.h>
#include <global_var.h>
#include <libft.h>

/*
static int	ft_pipe_fill(char in, char out, int fd_read, int fd_write, t_node *node,t_term *term)
{
	int		stdout;
	int		ret;

	if (!(g_pid = fork()))
	{
		stdout = dup(STDOUT_FILENO);
		if (in)
			dup2(fd_read, STDIN_FILENO);
		if (out)
			dup2(fd_write, STDOUT_FILENO);
		if (node->type == NODE_R_IN)
			ret = redirection(node->ch1, node->data, STDIN_FILENO, term);
		else if (node->type == NODE_R_OUT)
			ret = redirection(node->ch1, node->data, STDOUT_FILENO, term);
		else if (node->type == NODE_CMD)
			ret = simple_cmd(node, term, ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (wait(NULL) > 0)
		;
	g_pid = 0;

	return (ret);
}
*/

static int		ft_pipe_fill(t_pipe *p, t_node *node, t_term *term)
{
	int		ret;

	if (!(g_pid = fork()))
	{
		p->stdout = dup(STDOUT_FILENO);
		if (p->in)
			dup2(p->fd_read, STDIN_FILENO);
		if (p->out)
			dup2(p->fd_write, STDOUT_FILENO);
		if (node->type == NODE_R_IN)
			ret = redirection(node, STDIN_FILENO, term);
		else if (node->type == NODE_R_OUT)
			ret = redirection(node, STDOUT_FILENO, term);
		else if (node->type == NODE_CMD)
			ret = simple_cmd(node, term, ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (wait(NULL) > 0)
		;
	g_pid = 0;
	ft_bzero(p, sizeof(2));
	return (ret);
}

static t_pipe	*put_bool(t_pipe *p, char in, char out)
{
	p->in = in;
	p->out = out;
	return (p);
}

int				ft_pipe_fill2(t_pipe *p, t_node *job, t_term *term)
{
	int ret;

	close(p->fd_write);
	pipe(p->pipe_fd);
	p->fd_write = p->pipe_fd[1];
	ret = ft_pipe_fill(put_bool(p, 1, 1), job->ch1, term);
	close(p->fd_read);
	p->fd_read = p->pipe_fd[0];
	return (ret);
}

int				ft_pipe(t_node *node, t_term *term)
{
	t_pipe	p;
	t_node	*job;
	int		ret;

	if (!node)
		return (-1);
	pipe(p.pipe_fd);
	p.fd_write = p.pipe_fd[1];
	p.fd_read = p.pipe_fd[0];
	ret = ft_pipe_fill(put_bool(&p, 0, 1), node->ch1, term);
	job = node->ch2;
	while (job->ch2 && job->type == NODE_PIPE)
	{
		ret += ft_pipe_fill2(&p, job, term);
		job = job->ch2;
	}
	p.fd_read = p.pipe_fd[0];
	close(p.fd_write);
	ret += ft_pipe_fill(put_bool(&p, 1, 0), job, term);
	close(p.fd_write);
	close(p.fd_read);
	return (ret > 0 && ret < 42 ? 1 : ret); /* dont already know if a builtin can return 127 */
}

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