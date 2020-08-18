/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 19:29:17 by chamada           #+#    #+#             */
/*   Updated: 2020/08/18 19:29:19 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_term.h>

int		term_erase(t_term *t, int status)
{
	if (t->cursor.pos.x > 0)
	{
		tputs(t->caps.c_left, 0, &ft_putchar);
		tputs(t->caps.c_del, 0, &ft_putchar);
		t->cursor.pos.x--;
		line_erase_at(t->line, t->cursor.pos.x, 1);
	}
	return (status);
}
