/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:30:26 by chamada           #+#    #+#             */
/*   Updated: 2020/06/22 16:11:57 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ctype.h>

unsigned	ft_rand(unsigned min, unsigned max)
{
	static unsigned	rand = 0xACE1U;

	if (min == max)
			return (min);
	rand += 0x3AD;
	rand %= max;
	while (rand < min)
			rand = rand + max - min;
	return (rand);
}

char		*rand_key(unsigned len)
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
