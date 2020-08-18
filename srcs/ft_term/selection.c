/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 18:57:39 by chamada           #+#    #+#             */
/*   Updated: 2020/08/18 19:30:15 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_term.h>

void	highlight(t_term *t)
{
	if (t->select.start.x != -1U && t->select.end.x != -1U)
	{
		ft_dprintf(2, "[SELECT] start: %d, end: %d\n", t->select.start.x, t->select.end.x);
		tputs(tgoto(t->caps.c_move_h, 0, t->cursor.origin.x), 0, &ft_putchar);
		tputs(t->caps.c_del_line, 0, &ft_putchar);
		write(1, t->line->data, t->select.start.x);
		tputs(t->caps.standout, 0, &ft_putchar);
		write(1, t->line->data + t->select.start.x, t->select.end.x - t->select.start.x);
		tputs(t->caps.standout_end, 0, &ft_putchar);
		write(1, t->line->data + t->select.end.x, t->line->length - t->select.end.x);
		tputs(tgoto(t->caps.c_move_h, 0, t->cursor.origin.x + t->cursor.pos.x), 0, &ft_putchar);
	}
}

void	selection_left(t_term *t)
{
	if (t->cursor.pos.x > 0)
	{
		if (t->select.start.x == -1U || t->select.end.x == -1U)
		{
			t->select.start.x = t->cursor.pos.x;
			t->select.end.x = t->cursor.pos.x;
		}
		else
		{
			term_left(t);
			if (t->select.start.x == t->cursor.pos.x + 1)
				t->select.start.x = t->cursor.pos.x;
			else
				t->select.end.x = t->cursor.pos.x;
			highlight(t);
		}
	}
}

void	selection_right(t_term *t)
{
	if (t->cursor.pos.x < t->line->length)
	{
		if (t->select.start.x == -1U || t->select.end.x == -1U)
		{
			t->select.start.x = t->cursor.pos.x;
			t->select.end.x = t->cursor.pos.x;
		}
		else
		{
			term_right(t);
			if (t->select.end.x == t->cursor.pos.x - 1)
				t->select.end.x = t->cursor.pos.x;
			else
				t->select.start.x = t->cursor.pos.x;
			highlight(t);
		}
	}
}

void	selection_clear(t_term *t)
{
	if (t->select.start.x != -1U || t->select.end.x != -1U)
	{
		ft_dprintf(2, "[SELECT] clear\n");
		t->select.start.x = -1U;
		t->select.end.x = -1U;
		if (t->line)
		{
			tputs(tgoto(t->caps.c_move_h, 0, t->cursor.origin.x), 0, &ft_putchar);
			tputs(t->caps.c_del_line, 0, &ft_putchar);
			write(1, t->line->data,  t->line->length);
			tputs(tgoto(t->caps.c_move_h, 0, t->cursor.origin.x + t->cursor.pos.x), 0, &ft_putchar);
		}
	}
}
