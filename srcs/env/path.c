/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 21:16:09 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 07:53:18 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <sys/stat.h>
#include <map.h>
#include <stdlib.h>

static void	*unload_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char		**path_export(t_map *env)
{
	const t_map	*var = map_get(env, "PATH");
	char		*path;
	char		**split;

	if (!(path = var->value)
	|| !(split = ft_split(path, ':')))
	{
//		free(path);
		return (NULL);
	}
	//free(path);
	return (split);
}

char		*path_cat(const char *a, const char *b)
{
	const size_t	len = ft_strlen(a) + ft_strlen(b) + 1;
	char			*cat;
	char			*c;

	if (!(cat = ft_calloc(len + 1, sizeof(*cat))))
		return (NULL);
	c = cat;
	while (*a)
		*c++ = *a++;
	*c++ = '/';
	while (*b)
		*c++ = *b++;
	return (cat);
}

char		*path_get(t_map *env, const char *exec)
{
	char		**path;
	char		*join;
	struct stat	s;
	int			i;

	if (!exec || !*exec || !(path = path_export(env)))
		return (NULL);
	i = 0;
	while (path[i])
	{
		if (!(join = path_cat(path[i++], exec)))
			return (unload_strs(path));
		if (stat(join, &s) == 0 && s.st_mode & S_IXUSR)
		{
			unload_strs(path);
			return (join);
		}
		free(join);
	}
	unload_strs(path);
	return (NULL);
}
