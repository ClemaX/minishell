/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 19:29:52 by chamada           #+#    #+#             */
/*   Updated: 2020/08/18 21:17:22 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_term.h>

int			term_input(t_term *t, int status)
{
	int		ret;
	char	c;

	ret = read(0, &c, 1);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (c == '\033')
		return (term_input_escape(t, status));
	if (ft_iscntrl(c))
		return (term_input_control(t, status, c));
	selection_clear(t);
	if (!term_write(t, &c, 1))
		return ((status | TERM_ERROR) & ~TERM_READING);
	return (status);
}
