/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 15:33:02 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 04:04:52 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

void	cursor_del_range(t_term *term, int min, int max)
{
	int		new_x;
	int		len;

	if (!term->line || min > max)
		return ;
	new_x = term->cursor.x - (max - min);
	if (!(new_x >= 0 && new_x <= term->cursor.max.x))
		return ;
	term->cursor.x = new_x;
	term->cursor.max.x -= max - min;
	tputs(tgoto(term->caps.ch, 0, new_x + 9), 1, &ft_putchar);
	tputs(term->caps.dc_n, max - min, &ft_putchar);
	len = line_len(term->line);
	term->line = line_del_range(term->line, len - max, len - min, 0);
}

void	cursor_le(t_term *term)
{
	tputs(term->caps.le, 1, &ft_putchar);
	term->cursor.x--;
}

void	cursor_nd(t_term *term)
{
	tputs(term->caps.nd, 1, &ft_putchar);
	term->cursor.x++;
}

void	cursor_putc(t_term *term, char c)
{
	tputs(term->caps.im, 1, &ft_putchar);
	if (term->caps.ic)
		tputs(term->caps.ic, 1, &ft_putchar);
	write(1, &c, 1);
	line_insert_at_c(&term->line, term->cursor.x, c);
	term->cursor.x++;
	term->cursor.max.x++;
	if (term->caps.ip)
		tputs(term->caps.ip, 1, &ft_putchar);
	tputs(term->caps.ei, 1, &ft_putchar);
}