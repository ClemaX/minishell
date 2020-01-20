/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 22:33:25 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 07:11:53 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

static t_node	*simple_cmd(t_token **token)
{
	t_node	*result;
	t_node	*args;
	char	*exec_path;

	if (!(check_type(token, TOKEN, &exec_path)))
		return (NULL);
	args = arg_list(token);
	if (!(result = malloc(sizeof(*result))))
	{
		node_del(args);
		return (NULL);
	}
	result->type = NODE_CMD;
	result->data = exec_path;
	result->ch1 = args;
	result->ch2 = NULL;
	return (result);
}

static t_node	*cmd_get(t_token **token, t_token_t type, char file)
{
	t_node	*s_cmd;
	char	*file_path;
	t_node	*result;

	if (!(s_cmd = simple_cmd(token)))
		return (NULL);
	if (!check_type(token, type, NULL)
	|| (file && !(check_type(token, TOKEN, &file_path)))
	|| !(result = malloc(sizeof(*result))))
	{
		node_del(s_cmd);
		return (NULL);
	}
	result->type = (t_node_t)type;
	result->data = file_path;
	result->ch1 = s_cmd;
	result->ch2 = NULL;
	return (result);
}

t_node			*command(t_token **token)
{
	t_token			*save;
	t_node			*node;

	save = *token;
	if (((*token = save) && (node = cmd_get(token, OP_GREATER, 1)))
	|| ((*token = save) && (node = cmd_get(token, OP_LESSER, 1)))
	|| ((*token = save) && (node = simple_cmd(token))))
		return (node);
	*token = save;
	return (NULL);
}