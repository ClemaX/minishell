/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 07:14:07 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 07:38:50 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

int		cd(int ac, char **argv, char **envp)
{
	char	path[_POSIX_PATH_MAX];
	char	cwd[_POSIX_PATH_MAX];

	if (ac == 1 && ft_strcmp(argv[0], "cd", 3))
	{
		return (0);  /* have to go to home page here */
	}
	else if (ft_strcmp(argv[0], "cd", 3))
	{
		ft_bzero(path, _POSIX_PATH_MAX);
		ft_memcpy(path, argv[1]);
		if (path[0] == '/' && chdir(path) == 0)
			return (0);
		else
		{
			if (!(getcwd(cwd, sizeof(cwd))))
				return (1);
			ft_strcat(cwd, "/");
			ft_strcat(cwd, path);
			if (chdir(cwd) == 0)
				return (0);
		}
		return (1);
	}
}
