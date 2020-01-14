/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_test.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:48:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 07:35:35 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <libft.h>

void	map_print(t_map *map)
{
	if (map)
	{
		map_print(map->next);
		ft_printf("%s -> %s\n", map->key, map->value);
	}
}

int		map_test(void)
{
	t_map	*map;

	map = NULL;
	map_set(&map, "test", "TEST");
	map_set(&map, "A", "B");
	map_set(&map, "C", "D");
	map_print(map);
	ft_printf("%p\n", map_get(map, "missing"));
	ft_printf("%s\n", map_get(map, "A")->value);
	map_set(&map, "test", "WOW");
	map_set(&map, "C", "WTF");
	map_print(map);
	map_clr(&map);
	return (0);
}
