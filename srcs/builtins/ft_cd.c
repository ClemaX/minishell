/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 07:14:07 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 12:31:24 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <map.h>
#include <libft.h>

int		ft_cd(int ac, char **argv, t_map **env)
{
	char	path[_POSIX_PATH_MAX];
	char	cwd[_POSIX_PATH_MAX];

	if (ac == 1)
	{
		chdir(map_get(*env, "HOME")->value);
		map_set(env, "PWD", map_get(*env, "HOME")->value);
		return (0);
	}
	else
	{
		ft_bzero(path, _POSIX_PATH_MAX);
		ft_memcpy(path, argv[1], ft_strlen(argv[1]));
		if (path[0] == '/' && chdir(path) == 0)
		{
			map_set(env, "PWD", path);
			return (0);
		}
		else
		{
			if (!(getcwd(cwd, sizeof(cwd))))
				return (1);
			ft_strlcat(cwd, "/", ft_strlen(cwd) + 2);
			ft_strlcat(cwd, path, ft_strlen(cwd) + 2 + ft_strlen(path));
			if (chdir(cwd) == 0)
			{
				getcwd(cwd, sizeof(cwd));
				map_set(env, "PWD", cwd);
				return (0);
			}
		}
	}
	return (1);
}
