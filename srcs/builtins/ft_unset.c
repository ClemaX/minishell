/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unset.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 10:00:23 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 18:27:09 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <map.h>
#include <command.h>

int	ft_unset(t_cmd *cmd, char *name)
{
	while (cmd->ac-- > 1)
	{
		if (!arg_check(cmd->av[cmd->ac]))
		{
			ft_printf("%s: %s `%s' : not a valid identifier\n",
				name, cmd->av[0], cmd->av[cmd->ac]);
			return (1);
		}
		cmd->env = map_del(cmd->env, cmd->av[cmd->ac]);
		cmd->glob_env = map_del(cmd->glob_env, cmd->av[cmd->ac]);
	}
	return (0);
}
