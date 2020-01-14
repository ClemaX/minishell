/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_cd.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 07:14:07 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 11:17:13 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <libft.h>

int		ft_cd(int ac, char **argv, char **envp)
{
	char	path[_POSIX_PATH_MAX];
	char	cwd[_POSIX_PATH_MAX];

	(void)envp;
	if (ac == 1 && ft_strncmp(argv[0], "cd", 3))
	{
		return (0);  /* have to go to home page here */
	}
	else if (ft_strncmp(argv[0], "cd", 3))
	{
		ft_bzero(path, _POSIX_PATH_MAX);
		ft_memcpy(path, argv[1], ft_strlen(argv[1]));
		if (path[0] == '/' && chdir(path) == 0)
			return (0);
		else
		{
			if (!(getcwd(cwd, sizeof(cwd))))
				return (1);
			ft_strlcat(cwd, "/", ft_strlen(cwd) + 1);
			ft_strlcat(cwd, path, ft_strlen(cwd) + ft_strlen(path));
			if (chdir(cwd) == 0)
				return (0);
		}
	}
	return (1);
}
