/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   job.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 22:33:02 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 01:44:21 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

static t_node	*job_get(t_token **token)
{
	t_node	*result;
	t_node	*cmd;
	t_node	*job_node;

	if (!(cmd = command(token)))
		return (NULL);
	if ((!check_type(token, OP_PIPE, NULL)
	|| !(job_node = job(token)))
	|| !(result = malloc(sizeof(*result))))
	{
		node_del(cmd);
		return (NULL);
	}
	result->type = NODE_PIPE;
	result->ch1 = cmd;
	result->ch2 = job_node;
	return (result);
}

t_node			*job(t_token **token)
{
	t_token			*save = *token;
	t_node			*job_node;

	if (((*token = save)
		&& (job_node = job_get(token)))
	|| ((*token = save)
		&& (job_node = command(token))))
		return (job_node);
	return (NULL);
}
