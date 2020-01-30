/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:32:43 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 02:00:06 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <libft.h>
#include <unistd.h>

void	term_clear_line(t_term *term)
{
	tputs(tgoto(term->caps.ch, 0, 9), 1, &ft_putchar);
	tputs(term->caps.ce, 1, &ft_putchar);
	term->cursor.x = 0;
}

int		term_init(t_term *term, const char *term_type)
{
	if (!term_type
	|| (tgetent(NULL, term_type) <= 0)
	|| tcgetattr(0, &term->s_termios) == -1)
		return (-1);
	term->s_termios_bkp = term->s_termios;
	term->s_termios.c_lflag &= ~(ICANON | ECHO);
	term->copy = NULL;
	term->line = NULL;
	term->history = NULL;
	term->current = NULL;
	term->cursor = (t_cursor){.x=0, .y=0, .max={.x=0, .y=0}};
	caps_load(term);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->s_termios) == -1)
		return (-1);
	return (0);
}

int		term_destroy(t_term *term)
{
	if (tcsetattr(0, 0, &term->s_termios_bkp) == -1)
		return (-1);
	line_clr(&term->line);
	history_clr(&term->history);
	free(term->copy);
	map_clr(&term->env);
	free(term);
	return (0);
}