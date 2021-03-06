/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:53:19 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 16:09:30 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIFF_H
# define DIFF_H

# include <strings.h>

int	diff_s(const char *label, const char *got, const char *expected);
int	diff_p(const char *label, void *got, void *expected);
int	diff_i(const char *label, int got, int expected);
int	diff_size(const char *label, size_t got, size_t expected);
int	diff_ssize(const char *label, ssize_t got, ssize_t expected);
int	diff_bool(const char *label, char got, char expected);

#endif
