/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 16:34:23 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 18:53:04 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <libft.h>
#include <stdlib.h>

int	diff_s(const char *got, const char *expected)
{
	int	diff;

	if ((diff = ft_strcmp(got, expected)))
		ft_printf("%s: got: %s, expected: %s\n",
			RED"DIFF"RESET, got, expected);
	return (diff);
}

int	diff_p(const void *got, const void *expected)
{
	if (got != expected)
	{
		ft_printf("%s: got: %p, expected: %p\n",
			RED"DIFF"RESET, got, expected);
		return (1);
	}
	return (0);
}

int	run_test(const char *label, int fw, int (*test)())
{
	int	ret;

	ft_printf("%s %*s %s\n",
		BULLET, fw, label, (ret = (*test)()) ? PASS : FAIL);
	return (ret);
}

const char	*rand_key(int len)
{
	char	*key;
	char	c;

	if (!(key = malloc(sizeof(*key) * (len + 1))))
		return (NULL);
	key[--len] = '\0';
	while (len)
	{
		c = ft_rand('A', 'z');
		key[--len] = ft_isalnum(c) ? c : '_';
	}
	return (key);
}

const char	*rand_val(int len)
{
	char	*val;
	char	c;

	if (!(val = malloc(sizeof(*val) * (len + 1))))
		return (NULL);
	val[--len] = '\0';
	while (len)
	{
		c = ft_rand('A', 'z');
		val[--len] = ft_isalnum(c) ? c : '=';
	}
	return (val);
}

const char	**rand_tab_map(int count, int len)
{
	char	**tab;
	char	*key;
	char	*val;

	if (!(tab = malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	tab[--count] = NULL;
	while (count)
	{
		key = (char *)rand_key(ft_rand(1, len));
		val = (char *)rand_val(ft_rand(0, len));
		ft_asprintf(tab + --count, "%s=%s", key, val);
		free(key);
		free(val);
	}
	return ((const char **)tab);
}
