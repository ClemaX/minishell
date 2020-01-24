/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:32:43 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 20:20:59 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

void	caps_load(t_term *term)
{
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
}

void	clear_line(t_term *term)
{
	tputs(term->caps.le, term->cursor.x + 1, &ft_putchar);
	tputs(term->caps.ce, 1, &ft_putchar);
	term->cursor.x = 0;
}

int		caps_handler(t_term *term)
{
	char			buff[2];

	read(0, buff, 2);
	if (buff[1] == 'A' && term->line && term->line->prev)
	{
		term->line = term->line->prev;
		clear_line(term);
		ft_printf("%s", line_cat(&term->line->line, 0));
	}
	else if (buff[1] == 'B' && term->line && term->line->next)
	{
		term->line = term->line->next;
		clear_line(term);
		ft_printf("%s", line_cat(&term->line->line, 0));
	}
	else if (buff[1] == 'C' && term->cursor.x < term->cursor.max.x)
	{
		tputs(term->caps.nd, 1, &ft_putchar);
		term->cursor.x++;
	}
	else if (buff[1] == 'D' && term->cursor.x)
	{
		tputs(term->caps.le, 1, &ft_putchar);
		term->cursor.x--;
	}
//	ft_printf("%d", buff[1]);
	return (0);
}

int		term_init(t_term *term, const char *term_type)
{
	if (!term_type
	|| (tgetent(NULL, term_type) <= 0)
	|| tcgetattr(0, &term->s_termios) == -1)
		return (-1);
	term->s_termios_bkp = term->s_termios;
	term->s_termios.c_lflag &= ~(ICANON | ECHO);
	caps_load(term);
	if (tcsetattr(0, 0, &term->s_termios) == -1)
		return (-1);
	return (0);
}
