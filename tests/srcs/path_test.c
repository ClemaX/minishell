/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_test.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 22:59:05 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 20:41:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <stdlib.h>
#include <env.h>
#include <libft.h>

int	path_test(void)
{
	t_map	*env;
	char	*path;

	env = NULL;
	map_set(&env, "PATH", "/tmp:/usr/bin");
	path = path_get(env, "cd");
	ft_printf("%s\n", path);
	free(path);
	return (0);
}
