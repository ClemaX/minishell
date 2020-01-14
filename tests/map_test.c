/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_test.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:48:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 10:41:32 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <libft.h>

int	print(t_map *map)
{
	if (map)
	{
		ft_printf("%s=%s\n", map->key, map->value);
		print(map->next);
	}
	return (0);
}

int		map_test(int ac, const char **av, const char **ep)
{
	t_map	*map;

	(void)ac;
	map = map_load(ep);
	print(map);
	map_clr(&map);
	map = map_load(&av[1]);
	print(map);
	map_clr(&map);
	return (0);
}
