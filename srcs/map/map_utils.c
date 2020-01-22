/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 08:35:14 by chamada           #+#    #+#             */
/*   Updated: 2020/01/22 12:04:30 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <libft.h>
#include <map.h>
#include <stdlib.h>

static void	*unload_tab(char **tab)
{
	while (*tab)
		free(*tab++);
	return (NULL);
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

int			map_len(t_map *map)
{
	int	len;

	len = 0;
	while (map)
	{
		len++;
		map = map->next;
	}
	return (len);
}

char		**map_export(t_map *map)
{
	const int	count = map_len(map);
	int			len;
	char		**strs;
	char		**s;

	if (!count || !(strs = ft_calloc(count + 1, sizeof(*strs))))
		return (NULL);
	s = strs;
	while (map)
	{
		len = map->key_size + ft_strlen(map->value);
		if (!(*s = malloc((sizeof(**s) * len) + 1)))
			return (unload_tab(strs));
		ft_memcpy(*s, map->key, map->key_size - 1);
		(*s)[map->key_size - 1] = '=';
		ft_memcpy(&(*s)[map->key_size], map->value, len - map->key_size);
		(*s)[len] = '\0';
		s++;
		map = map->next;
	}
	return (strs);
}
