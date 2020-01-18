/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arg_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 17:40:37 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 01:25:14 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <command.h>

int		key_check(char *key)
{
	while (*key)
	{
		if (!((ft_isalnum(*key)) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

void	arg_add(t_token **args, t_token **arg, t_cmd *cmd)
{
	(*arg)->next = *args;
	*args = *arg;
	*arg = NULL;
	cmd->ac++;
}

void	args_clr(t_token **args, t_cmd *cmd)
{
	t_token	*curr;

	while ((curr = *args))
	{
		*args = (*args)->next;
		free(curr->data);
		free(curr);
	}
	free(cmd->av);
	cmd->ac = 0;
	cmd->av = NULL;
}
