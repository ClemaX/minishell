/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 16:03:42 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 05:22:50 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <command.h>
#include <libft.h>

int	print_env(t_map *map)
{
	if (map)
	{
		if (map->value && *map->value)
			ft_printf("declare -x %s=\"%s\"\n", map->key, map->value);
		else
			ft_printf("declare -x %s\n", map->key);
		print_env(map->next);
	}
	return (0);
}

int	ft_export(t_cmd *cmd, char *name)
{
	t_map	*var;

	if (cmd->ac == 1)
	{
		map_sort(&cmd->env, &map_cmp);
		print_env(cmd->env);
	}
	else
	{
		while (cmd->ac-- > 1)
		{
			if (!key_check(cmd->av[cmd->ac]))
			{
				ft_printf("%s: %s `%s' : not a valid identifier\n",
					name, cmd->av[0], cmd->av[cmd->ac]);
				return (1);
			}
			if ((var = map_get(cmd->env, cmd->av[cmd->ac])) &&
				!map_set(&cmd->env, var->key, var->value))
				return (1);
			else if (!map_set(&cmd->env, cmd->av[cmd->ac], ""))
				return (1);
		}
	}
	return (0);
}
