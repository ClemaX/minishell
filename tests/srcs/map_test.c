/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_test.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:48:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 18:53:15 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <map.h>
#include <libft.h>
#include <stdlib.h>

int	map_print(t_map *map)
{
	if (map)
	{
		ft_printf("%s=%s\n", map->key, map->value);
		map_print(map->next);
	}
	return (0);
}

int	map_set_test(void)
{
	static const t_map	orig = (t_map){.key="KEY", .value="value"};
	t_map				*map;
	int					diff;

	map = NULL;
	if (!(map_set(&map, orig.key, orig.value)))
		error();
	diff = diff_s(map->value, orig.value)
		+ diff_s(map->key, orig.key)
		+ diff_p(map->next, NULL);
	free(map->key);
	free(map->value);
	free(map);
	return (!diff);
}

int	map_get_test(void)
{
	static const t_map	orig[2] = {\
		(t_map){.key="A", .value="B"},\
		(t_map){.key="C", .value="D"}};
	t_map				*map;
	t_map				*got[2];
	int					diff;
	int					i;

	map = NULL;
	i = 0;
	diff = 0;
	while (i < 2)
	{
		if (!(map_set(&map, orig[i].key, orig[i].value)))
			error();
		if (!(got[i] = map_get(map, orig[i].key)))
		{
			diff_s(NULL, orig[i].value);
			map_clr(&map);
			return (0);
		}
		diff += diff_s(got[i]->value, orig[i].value)
			+ diff_s(got[i]->key, orig[i].key);
		i++;
	}
	map_clr(&map);
	return (!diff);
}

int	map_export_test(void)
{
	const char	**orig = rand_tab_map(25, 20);
	t_map		*map;
	char		**strs;
	int			diff;

	if (!(map = map_load(orig))
	|| !(strs = map_export(map)))
		error();
	diff = tab_cmp(strs, orig);
	strs = tab_unload(strs);
	orig = tab_unload((char **)orig);
	map_clr(&map);
	return (!diff);
}

int	map_clr_test(void)
{
	t_map	*map;

	map = NULL;
	if (!map_set(&map, "A", "B")
	|| !map_set(&map, "C", "D"))
	{
		map_clr(&map);
		error();
	}
	map_clr(&map);
	return (!diff_p(map, NULL));
}

int	map_test(int ac, const char **av, const char **ep)
{
	static const int	fw = -10;

	(void)ac;
	ft_printf(TITLE"Map\n"RESET);
	run_test("map_set", fw, &map_set_test);
	run_test("map_get", fw, &map_get_test);
	run_test("map_export", fw, &map_export_test);
	run_test("map_clr", fw, &map_clr_test);
	return (0);
}
