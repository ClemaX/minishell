/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_test.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:48:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 09:44:58 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <libft.h>

int		map_test(int ac, const char **av, const char **ep)
{
	t_map	*map;

	(void)ac;
	(void)av;
	map = map_load(ep);
	map_print(map);
	map_clr(&map);
	map = map_load(&av[1]);
	map_print(map);
	map_clr(&map);
	return (0);
}
