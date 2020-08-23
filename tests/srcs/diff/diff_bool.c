/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:10:29 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 15:51:28 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>
#include <stdio.h>

int		diff_bool(const char *label, char got, char expected)
{
	const char *bool_values[2] = {"false", "true"};

	if (got != expected)
	{
		printf("\n%s: %s: %s expected: %s ",
			RED"DIFF"RESET, label, bool_values[(unsigned char)got],
				bool_values[(unsigned char)expected]);
		return (1);
	}
	return (0);
}
