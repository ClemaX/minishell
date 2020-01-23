/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:51:41 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/23 19:09:42 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <execution.h>
#include "global_var.h"

/* have to end lexer token predefinition for test that */

int     double_redirection(t_node *node, char *data, char std, t_map *env, char *name)
{
    int     stdout;
    int     fd;

    if (!node || !data)
        return (-1);
    if ((g_pid = fork()) == 0)
    {
        stdout = dup(STDOUT_FILENO);
        if (!std) /* << */
        {
            /* check 1st word and read and store to sdtdin until this word is alone in a new line 
                data between the 2 delim words will be buiting input
            */
        }
		else /* >> */
		{
			if ((fd = open(data, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC,
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
	g_pid = 0;
}
