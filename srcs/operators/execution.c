/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execution.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 03:41:36 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 18:23:52 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include <execution.h>
#include <command.h>
#include "parser.h"
#include "unistd.h"
#include <libft.h>
#include <stdlib.h>

static int		cmd_execution(t_node *node, t_map *env, char *name)
{
	if (!node)
		return (-1);
	if (node->type == NODE_R_IN)
		return (redirection(node, STDIN_FILENO, env, name));
	else if (node->type == NODE_R_OUT)
		return (redirection(node, STDOUT_FILENO, env, name));
	else if (node->type == NODE_CMD)
		return (simple_cmd(node, env, name, ft_execve_f));
}

static int		job_execution(t_node *node, t_map *env, char *name)
{
	if (!node)
		return (-1);
	if (node->type == NODE_PIPE)
		return (ft_pipe(node, env, name));
	else
		return (cmd_execution(node, env, name));
}

void			cmd_line_execution(t_node *node, t_map *env, char *name)
{
	int ret;

	ret = 0; /* ret is 0 by default does not need initiaisation but i $? with no execution it have to be 0 */
	if (!node)
		return ;
	if (node->type == NODE_SEQ)
	{
		ret = job_execution(node->ch1, env, name);
		cmd_line_execution(node->ch2, env, name);
	}
	else
		ret = job_execution(node, env, name);
	ft_printf("%d\n", ret);
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

int		simple_cmd(t_node *node, t_map *env, char *name,
	int (exec)(char *, t_cmd *))
{
	t_cmd	cmd;
	int		ret;

	ret = -1;
	if (node)
	{
		cmd.glob_env = env;
		cmd.env = env;
		if (init_cmd(node, &cmd))
			ret = cmd_exec(&cmd, name, exec);
	}
	return (ret);
}
