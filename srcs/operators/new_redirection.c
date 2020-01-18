/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   new_redirection.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 05:42:36 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 06:37:07 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>

void		redirection(t_node *node, char *data, char std)
{
	// check if we have content (if something is NULL idk)
	int		pid;
	int		stdout;
	int		fd;

	if ((pid = fork()) == 0)
	{
		// restore_sigin_in_child() ???
		stdout = dup(STDOUT_FILENO); // need this ?
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
	}
	else if (pid < 0)
		return ;
	while (waitpid(pid, NULL, 0) <= 0)
		;
}

void		simple_cmd(t_node *node)
{
	/* call minish()
	not founded ? search in /bin
	not founded ? printf("comand not found") */
}
