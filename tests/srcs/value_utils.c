/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   value_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 19:29:51 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 20:32:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

const char	*rand_key(int len)
{
	char	*key;
	char	c;

	if (!(key = malloc(sizeof(*key) * (len + 1))))
		return (NULL);
	key[len] = '\0';
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
	val[len] = '\0';
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
