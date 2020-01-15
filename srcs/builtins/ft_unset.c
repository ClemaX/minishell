/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_unset.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 10:00:23 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 13:09:57 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <map.h>

int	ft_unset(int ac, char **av, t_map **map)
{
	while (ac > 1)
		*map = map_del(*map, av[--ac]);
	return (0);
}
