/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:30:26 by chamada           #+#    #+#             */
/*   Updated: 2020/06/15 20:55:34 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>

unsigned int	ft_rand(unsigned int min, unsigned int max)
{
	static unsigned int	rand = 0xACE1U;

	if (min == max)
			return (min);
	rand += 0x3AD;
	rand %= max;
	while (rand < min)
			rand = rand + max - min;
	return (rand);
}

char			*rand_key(int len)
{
	char	*key;
	char	c;

	if (!(key = malloc(sizeof(*key) * (len + 1))))
			return (NULL);
	key[len] = '\0';
	while (len)
	{
			c = ft_rand('A', 'z');
			key[--len] = c;
	}
	return (key);
}
