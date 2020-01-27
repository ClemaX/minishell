/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 03:41:36 by chamada           #+#    #+#             */
/*   Updated: 2020/01/27 16:14:11 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <execution.h>
#include <command.h>
#include "parser.h"
#include "unistd.h"
#include <libft.h>
#include <stdlib.h>

static int		cmd_execution(t_node *node, t_term *term)
{
	if (!node)
		return (-1);
	if (node->type == NODE_R_IN)
		return (redirection(node, STDIN_FILENO, term));
	else if (node->type == NODE_R_OUT)
		return (redirection(node, STDOUT_FILENO, term));
	else if (node->type == NODE_CMD)
		return (simple_cmd(node, term, ft_execve_f));
	else
		return (-1); /* Not implemented */
}

static int		job_execution(t_node *node, t_term *term)
{
	if (!node)
		return (-1);
	if (node->type == NODE_PIPE)
		return (ft_pipe(node, term));
	else
		return (cmd_execution(node, term));
}

void			cmd_line_execution(t_node *node, t_term *term)
{

	term->ret = 0; /* ret is 0 by default does not need initiaisation but i $? with no execution it have to be 0 */
	if (!node)
		return ;
	if (node->type == NODE_SEQ)
	{
		term->ret = job_execution(node->ch1, term);
		cmd_line_execution(node->ch2, term);
	}
	else
	term->ret = job_execution(node, term);
	ft_printf("%d\n", term->ret);
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

int		simple_cmd(t_node *node, t_term *term,
	int (exec)(char *, t_cmd *))
{
	t_cmd	cmd;
	int		ret;

	ret = -1;
	if (node)
	{
		cmd.glob_env = term->env;
		cmd.env = term->env;
		if (init_cmd(node, &cmd))
			ret = cmd_exec(&cmd, term->name, exec);
	}
	return (ret);
}
