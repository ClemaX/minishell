/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_test.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:48:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 23:08:19 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <libft.h>
#include <stdlib.h>

int	print(t_map *map)
{
	if (map)
	{
		ft_printf("%s=%s\n", map->key, map->value);
		print(map->next);
	}
	return (0);
}

int	print_tab(char **tab)
{
	if (!tab)
		return (0);
	while (*tab)
		ft_printf("%s\n", *tab++);
	return (0);
}

static void	*unload_tab(char **tab)
{
	while (*tab)
		free(*tab++);
	return (NULL);
}

int	map_test(int ac, const char **av, const char **ep)
{
	t_map	*map;
	char	**strs;

	(void)ac;
	map = map_load(ep);
	strs = map_export(map);
	print_tab(strs);
	strs = unload_tab(strs);
	print_tab(strs);
	map_clr(&map);
	map = map_load(&av[1]);
	print(map);
	map_clr(&map);
	return (0);
}
