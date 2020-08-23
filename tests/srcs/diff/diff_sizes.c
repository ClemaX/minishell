/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_sizes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:10:31 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 15:50:04 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>
#include <string.h>
#include <stdio.h>

int		diff_size(const char *label, size_t got, size_t expected)
{
	if (got != expected)
	{
		printf("\n%s: %s: %zu, expected: %zu ",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}

int		diff_ssize(const char *label, ssize_t got, ssize_t expected)
{
	if (got != expected)
	{
		printf("\n%s: %s: %zd, expected: %zd ",
			RED"DIFF"RESET, label, got, expected);
		return (1);
	}
	return (0);
}
