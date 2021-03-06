#include "builtins.h"

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

int	ft_export(int ac, char **av, t_term *t)
{
	t_map	*var;

	if (ac == 1)
	{
		map_sort(&t->env, &map_cmp);
		print_env(t->env);
	}
	else
	{
		while (ac-- > 1)
		{
			/* if (!key_check(av[ac]))
			{
				ft_printf("%s: %s `%s' : not a valid identifier\n",
					t->name, av[0], av[ac]);
				return (1);
			} */
			if ((var = map_get(t->env, av[ac])))
			{
				if (!map_set(&t->env, var->key, var->value))
					return (1);
			}
			else if (!map_set(&t->env, av[ac], ""))
				return (1);
		}
	}
	return (0);
}
