/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 05:42:36 by chamada           #+#    #+#             */
/*   Updated: 2020/01/22 13:56:20 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <execution.h>
#include "global_var.h"

void	redirection(t_node *node, char *data, char std, t_map *env, char *name)
{

	int		stdout;
	int		fd;

	if (!node || !data)
		return ;
	if ((g_pid = fork()) == 0)
	{
		stdout = dup(STDOUT_FILENO); // need this , think is 4 error check?
		if (!std)
		{
			if ((fd = open(data, O_RDONLY)) < 0)
				return ;
			dup2(fd, STDIN_FILENO);
		}
		else
		{
			if ((fd = open(data, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
				return ;
			dup2(fd, STDOUT_FILENO);
		}
		simple_cmd(node, env, name, &ft_execve);
	}
	else if (g_pid < 0)
		return ;
	while (waitpid(g_pid, NULL, 0) <= 0)
		;
}
