/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wildcard.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 01:08:04 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 17:05:35 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int			whildcard(char *to_find, char *document)
{
	unsigned i;
	char *pos;
	const char **tokens = ft_split(to_find, '*');

	i = 0;
	while (tokens[i])
	{
		const unsigned len = ft_strlen(tokens[i]);
		if ((pos = ft_strnstr(document, tokens[i], len)))
			return (0);
		free(tokens[i++]);
		while ((unsigned)document < (unsigned)pos + len - 1)
			document++;
	}
	return (1);
}
