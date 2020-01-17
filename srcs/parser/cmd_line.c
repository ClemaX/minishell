/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cmd_line.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 22:29:42 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 23:08:40 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

static t_node	*cmd_line_get(t_token **token, t_token_t type, char recur)
{
	t_node	*job_node;
	t_node	*cmd_line_node;
	t_node	*result;

	if (!(job_node = job(token)))
		return (NULL);
	if (!check_type(token, type, NULL)
	|| (recur && !(cmd_line_node = cmd_line(token)))
	|| !(result = malloc(sizeof(*result))))
	{
		node_del(job_node);
		return (NULL);
	}
	result->type = type;
	result->ch1 = job_node;
	result->ch2 = (recur) ? cmd_line_node : NULL;
	return (result);
}

t_node			*cmd_line(t_token **token)
{
	const t_token	*save = *token;
	t_node			*node;

	if ((((*token) = save)
		&& (node = cmd_line_get(token, OP_SEMICOLON, 1)))
	|| (((*token) = save)
		&& (node = cmd_line_get(token, OP_SEMICOLON, 0)))
	|| (((*token) = save)
		&& (node = cmd_line_get(token, OP_AMPERSAND, 1)))
	|| (((*token) = save)
		&& (node = cmd_line_get(token, OP_AMPERSAND, 0)))
	|| (((*token) = save)
		&& (node = job(token))))
		return (node);
	return (NULL);
}
