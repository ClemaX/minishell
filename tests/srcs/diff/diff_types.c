/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:30:53 by chamada           #+#    #+#             */
/*   Updated: 2020/05/21 19:52:41 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include <tests.h>
#include <stdio.h>
#include <string.h>

int		diff_s(const char *label, const char *got, const char *expected)
{
	int	diff;

	if ((diff = strcmp(got, expected)))
		printf("%s: %s: %s, expected: %s",
			RED"DIFF"RESET, label, got, expected);
	return (diff != 0);
}

int		diff_p(const char *label, void *got, void *expected)
{
	if (got != expected)
	{
		printf("%s: %s: %p, expected: %p",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}

int		diff_i(const char *label, int got, int expected)
{
	if (got != expected)
	{
		printf("%s: %s: %d, expected: %d",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}
