/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   double_redirection.c                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 16:58:58 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 22:36:51 by chamada     ###    #+. /#+    ###.fr     */
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

static int	double_rediretion_fill(int fd, char *data, char bool)
{
	if (bool)
	{
		if ((fd = open(data, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
		dup2(fd, STDOUT_FILENO);
	}
	else
	{
		/* check 1st word and read and store to sdtdin until this word is alone in a new line 
				data between the 2 delim words will be buiting input
			*/
	}
	return (1);
}

int			double_redirection(t_node *node, char *data, char std, t_term *term)
{
	int	stdout;
	int	fd;

	if (!node || !data)
		return (-1);
	if ((g_pid = fork()) == 0)
	{
		stdout = dup(STDOUT_FILENO);
		if (!std)
		{
			if ((double_redirection_fill(fd, data, std)) < 0)
				return (-1);
		}
		else
			if ((double_redirection_fill(fd, data, std)) < 0)
				return (-1);
		simple_cmd(node, term, &ft_execve);
	}
	else if (g_pid < 0)
		return (-1);
	while (waitpid(g_pid, NULL, 0) <= 0)
		;
	g_pid = 0;
}

