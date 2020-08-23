/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:30:53 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 15:49:50 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>
#include <stdio.h>
#include <string.h>

int		diff_s(const char *label, const char *got, const char *expected)
{
	int								diff;
	static const char				*null_str = "(null)";

	if (!got)
		got = null_str;
	if (!expected)
		expected = null_str;
	if ((diff = strcmp(got, expected)))
		printf("\n%s: %s: %s, expected: %s ",
			RED"DIFF"RESET, label, got, expected);
	return (diff != 0);
}

int		diff_p(const char *label, void *got, void *expected)
{
	if (got != expected)
	{
		printf("\n%s: %s: %p, expected: %p ",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}

int		diff_i(const char *label, int got, int expected)
{
	if (got != expected)
	{
		printf("\n%s: %s: %d, expected: %d ",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}
