/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 03:41:36 by chamada           #+#    #+#             */
/*   Updated: 2020/01/22 11:43:14 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <execution.h>
#include <command.h>
#include "parser.h"
#include "unistd.h"
#include <libft.h>
#include <stdlib.h>


static void		cmd_execution(t_node *node, t_map *env, char *name)
{
	if (!node)
		return ;
	if (node->type == NODE_R_IN)
		redirection(node->ch1, node->data, STDIN_FILENO, env, name);
	else if (node->type == NODE_R_OUT)
		redirection(node->ch1, node->data, STDOUT_FILENO, env, name);
	else if (node->type == NODE_CMD)
		simple_cmd(node, env, name, ft_execve_f);
}

static void		job_execution(t_node *node, t_map *env, char *name)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		ft_pipe(node, env, name);
	else
		cmd_execution(node, env, name);
}

void			cmd_line_execution(t_node *node, t_map *env, char *name)
{
	if (!node)
		return ;
	if (node->type == NODE_SEQ)
	{
		job_execution(node->ch1, env, name);
		cmd_line_execution(node->ch2, env, name);
	}
	else
		job_execution(node, env, name);
}

int			init_cmd(t_node *node, t_cmd *cmd)
{
	t_node	*curr;
	int		i;

	if (!node->data || !*node->data)
		return (0);
	cmd->ac = 0;
	curr = node;
	while (curr)
	{
		cmd->ac++;
		curr = curr->ch1;
	}
	if (!(cmd->av = malloc(sizeof(*cmd->av) * (cmd->ac + 1))))
		return (-1);
	i = 0;
	cmd->av[i++] = node->data;
	curr = node->ch1;
	while (curr)
	{
		cmd->av[i++] = curr->data;
		curr = curr->ch1;
	}
	cmd->av[i] = NULL;
	return (1);
}

void		simple_cmd(t_node *node, t_map *env, char *name, int (exec)(char *, t_cmd *))
{
	t_cmd	cmd;

	if (node)
	{
		cmd.glob_env = env;
		cmd.env = env;
		if (init_cmd(node, &cmd))
			cmd_exec(&cmd, name, exec);
	}
}
