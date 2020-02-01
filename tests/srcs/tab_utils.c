/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tab_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 16:04:24 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 05:52:09 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <stdlib.h>
#include <libft.h>

int		tab_print(char **tab)
{
	if (!tab)
		return (0);
	while (*tab)
		ft_printf("%s\n", *tab++);
	return (0);
}

void	*tab_unload(char **tab)
{
	char	**start;

	start = tab;
	while (*tab)
		free(*tab++);
	free(start);
	return (NULL);
}

int		tab_cmp(char **tab, char **expected)
{
	if (!tab && expected)
	{
		ft_printf("%s: tab is NULL\n",
			RED"ERROR"RESET);
		return (1);
	}
	while (*tab && *expected && !diff_s(*tab, *expected))
	{
		tab++;
		expected++;
	}
	return (*tab || *expected);
}
