/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   caps.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/27 19:20:42 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 03:36:15 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <unistd.h>

void	caps_load(t_term *term)
{
	term->caps.im = tgetstr("im", NULL);
	term->caps.ei = tgetstr("ei", NULL);
	term->caps.cm = tgetstr("cm", NULL);
	term->caps.ho = tgetstr("ho", NULL);
	term->caps.cl = tgetstr("cl", NULL);
	term->caps.ku = tgetstr("ku", NULL);
	term->caps.kd = tgetstr("kd", NULL);
	term->caps.kl = tgetstr("kl", NULL);
	term->caps.kr = tgetstr("kr", NULL);
	term->caps.le = tgetstr("le", NULL);
	term->caps.nd = tgetstr("nd", NULL);
	term->caps.ce = tgetstr("ce", NULL);
	term->caps.ch = tgetstr("ch", NULL);
	term->caps.cr = tgetstr("cr", NULL);
	term->caps.ec = tgetstr("ec", NULL);
	term->caps.dc_n = tgetstr("dc_n", NULL);
}

int		caps_handler(t_term *term)
{
	char			buff[2];

	if (read(0, buff, 2) != 2)
		return (0);
	if (buff[1] == 'A')
		history_prev(term);
	else if (buff[1] == 'B')
		history_next(term);
	else if (buff[1] == 'C' && term->cursor.x < term->cursor.max.x)
		cursor_nd(term);
	else if (buff[1] == 'D' && term->cursor.x)
		cursor_le(term);
	return (0);
}
