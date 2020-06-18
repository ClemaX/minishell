/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:10:29 by chamada           #+#    #+#             */
/*   Updated: 2020/05/21 20:26:59 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include <tests.h>
#include <stdio.h>

int		diff_bool(const char *label, char got, char expected)
{
	const char *boolValues[2] = {"false", "true"};
	if (got != expected)
	{
		printf("%s: %s: %s expected: %s",
			RED"DIFF"RESET, label, boolValues[(unsigned char)got], boolValues[(unsigned char)expected]);
		return (1);
	}
	return (0);
}
