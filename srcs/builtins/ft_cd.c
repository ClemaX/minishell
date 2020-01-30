/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 07:14:07 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 05:19:27 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <command.h>
#include <libft.h>
#include <env.h>

int		ft_cd(t_cmd *cmd)
{
	char	cwd[_POSIX_PATH_MAX];
	char	*path;

	if (cmd->ac == 1)
		path = map_get(cmd->env, "HOME")->value;
	else
	{
		path = cmd->av[1];
		if (path[0] != '/')
		{
			if (!(getcwd(cwd, _POSIX_PATH_MAX)))
				return (1);
			path = path_cat(cwd, path);
		}
	}
	if (chdir(path) == 0)
	{
		map_set(&cmd->env, "PWD", path);
		return (0);
	}
	return (1);
}
