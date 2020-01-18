/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arg_list.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 22:39:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 01:47:01 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <parser.h>
#include <stdlib.h>

t_node	*arg_list(t_token **token)
{
	t_node	*arg_list_node;
	t_node	*result;
	char	*arg;

	if (!check_type(token, TOKEN, &arg))
		return (NULL);
	arg_list_node = arg_list(token);
	if (!(result = malloc(sizeof(*result))))
	{
		node_del(arg_list_node);
		return (NULL);
	}
	result->type = NODE_ARG;
	result->data = arg;
	result->ch1 = arg_list_node;
	result->ch2 = NULL;
	return (result);
}
