/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 08:35:14 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 18:29:30 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include <libft.h>
#include <map.h>
#include <stdlib.h>

static void	*unload_strs(char **strs)
{
	while (*strs)
		free(*strs++);
	return (NULL);
}

const char	*map_add(t_map **map, const char *key, const char *value)
{
	t_map		*new;

	if (!map || !key || !value)
		return (NULL);
	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	*new = (t_map){.key=ft_strdup(key), .key_size=ft_strlen(key),
		.value=ft_strdup(value), .next=*map};
	if (!new->key || !new->value)
	{
		map_delone(new);
		return (NULL);
	}
	return ((*map = new)->value);
}

t_map		*map_load(const char **strs)
{
	t_map	*map;
	char	**split;

	if (!strs || !*strs)
		return (NULL);
	map = NULL;
	while (*strs)
	{
		if (!(split = ft_split(*strs, '=')))
			return (NULL);
		if (!split[0] || !split[1])
		{
			unload_strs(split);
			return (NULL);
		}
		map_add(&map, split[0], split[1]);
		unload_strs(split);
		free(split);
		strs++;
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
			return (unload_strs(strs));
		ft_memcpy(*s, map->key, map->key_size - 1);
		(*s)[map->key_size - 1] = '=';
		ft_memcpy(&(*s)[map->key_size], map->value, len - map->key_size);
		(*s)[len] = '\0';
		s++;
		map = map->next;
	}
	return (strs);
}
