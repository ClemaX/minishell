/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirection.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 05:42:36 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 22:35:52 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <execution.h>
#include "global_var.h"
#include <prompt.h>

int		redirection_fill(char *data, char bool)
{
	int	fd;

	if (bool)
	{
		if ((fd = open(data, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		if ((fd = open(data, O_RDONLY)) < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	return (0);
}

int		redirection(t_node *node, char std, t_term *term)
{
	int		stdout;
	int		ret;

	if (!node->ch1 || !node->data)
		return (-1);
	if ((g_pid = fork()) == 0)
	{
		stdout = dup(STDOUT_FILENO); // need this , think is 4 error check?
		if ((redirection_fill(node->data, std) < 0))
			return (-1);
		ret = simple_cmd(node->ch1, term, &ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (waitpid(g_pid, NULL, 0) <= 0)
		;
	g_pid = 0;
	return (ret);
}

/*

int		redirection(t_node *node, char *data, char std,t_term *term)
{
	int		stdout;
	int		fd;
	int		ret;

	if (!node || !data)
		return (-1);
	if ((g_pid = fork()) == 0)
	{
		stdout = dup(STDOUT_FILENO); // need this , think is 4 error check?
		if ((redirection_fill(fd, data, std) < 0))
			return (-1);
		ret = simple_cmd(node, env, name, &ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (waitpid(g_pid, NULL, 0) <= 0)
		;
	g_pid = 0;
	return (ret);
}
*/