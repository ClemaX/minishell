/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 08:35:14 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 09:51:22 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <map.h>
#include <stdlib.h>

static void	unload_tab(char **tab)
{
	while (*tab)
		free(*tab++);
}

t_map		*map_load(const char **tab)
{
	t_map	*map;
	char	**split;

	if (!tab || !*tab)
		return (NULL);
	map = NULL;
	while (*tab)
	{
		if (!(split = ft_split(*tab, '=')))
			return (NULL);
		if (!split[0] || !split[1])
		{
			unload_tab(split);
			return (NULL);
		}
		map_set(&map, split[0], split[1]);
		unload_tab(split);
		free(split);
		tab++;
	}
	return (map);
}
