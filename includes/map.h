/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   map.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 05:51:26 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 07:19:03 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>

typedef struct	s_map
{
	char			*key;
	size_t			key_size;
	char			*value;
	struct s_map	*next;
}				t_map;

const char		*map_set(t_map **map, const char *key, const char *value);
t_map			*map_get(t_map *map, const char *key);
void			map_delone(t_map *elem);
t_map			*map_del(t_map *map, const char *key);
void			map_clr(t_map **map);

#endif