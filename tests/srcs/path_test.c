/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   path_test.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 22:59:05 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 05:42:40 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <map.h>
#include <stdlib.h>
#include <env.h>
#include <libft.h>

int	path_cat_test(void)
{
	static const char	*a = "FGHIJ";
	static const char	*b = "ABC DEF";
	static const char	*expected = "FGHIJ/ABC DEF";
	char				*got;

	if (!(got = path_cat(a, b)))
		error();
	if (diff_s(got, (char *)expected))
	{
		free(got);
		return (0);
	}
	free(got);
	return (1);
}

int	path_get_test(void)
{
	t_map	*env;
	char	*path;
	int		diff;

	env = NULL;
	map_set(&env, "PATH", "/bin:/usr/bin");
	path = path_get(env, "cd");
	diff = diff_s(path, "/usr/bin/cd");
	free(path);
	path = path_get(env, "cat");
	diff += diff_s(path, "/bin/cat");
	free(path);
	path = path_get(env, "xzarble");
	diff += diff_p(path, NULL);
	free(path);
	map_clr(&env);
	return (!diff);
}

int	path_test(void)
{
	static const int fw = -8;

	ft_printf(TITLE"Path\n"RESET);
	run_test("path_cat", fw, &path_cat_test);
	run_test("path_get", fw, &path_get_test);
	return (0);
}
