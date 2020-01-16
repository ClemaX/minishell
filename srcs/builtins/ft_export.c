/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_export.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 16:03:42 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 20:34:04 by chamada     ###    #+. /#+    ###.fr     */
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

int	ft_export(int ac, char **av, t_cmd *cmd, char *name)
{
	t_map	*var;

	if (ac == 1)
	{
		map_sort(&cmd->glob_env, &map_cmp);
		print_env(cmd->glob_env);
	}
	else
	{
		while (ac-- > 1)
		{
			if (!key_check(av[ac]))
			{
				ft_printf("%s: %s `%s' : not a valid identifier\n",
					name, av[0], av[ac]);
				return (1);
			}
			if ((var = map_get(cmd->env, av[ac])))
			{
				if (!map_set(&cmd->glob_env, var->key, var->value))
					return (1);
			}
			else if (!map_set(&cmd->glob_env, av[ac], ""))
				return (1);
		}
	}
	return (0);
}
