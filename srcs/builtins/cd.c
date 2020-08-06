#include "builtins.h"

int		ft_cd(int ac, char **argv, t_term *t)
{
	char	path[PATH_MAX];
	char	cwd[PATH_MAX];

	if (ac == 1)
	{
		chdir(map_get(t->env, "HOME")->value);
		map_set(&t->env, "PWD", map_get(t->env, "HOME")->value);
		return (0);
	}
	else
	{
		ft_bzero(path, PATH_MAX);
		ft_memcpy(path, argv[1], ft_strlen(argv[1]));
		if (path[0] == '/' && chdir(path) == 0)
		{
			map_set(&t->env, "PWD", path);
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
				map_set(&t->env, "PWD", cwd);
				return (0);
			}
		}
	}
	return (1);
}
