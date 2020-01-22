/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:32:43 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 13:54:43 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>

void	caps_load(t_caps *caps)
{
	caps->cm = tgetstr("cm", NULL);
	caps->ho = tgetstr("ho", NULL);
	caps->cl = tgetstr("cl", NULL);
	caps->ku = tgetstr("ku", NULL);
	caps->kd = tgetstr("kd", NULL);
	caps->kl = tgetstr("kl", NULL);
	caps->kr = tgetstr("kr", NULL);
}

int		caps_handler(t_term *term)
{
	(void)term;
	return (0);
}

int		term_init(t_term *term, const char *term_type)
{
	struct termios	s_termios;

	if (term_type
	|| (tgetent(NULL, term_type) <= 0)
	|| tcgetattr(0, &s_termios) == -1)
		return (-1);
	term->s_termios_bkp = s_termios;
	s_termios.c_lflag &= ~(ICANON & ECHO);
	caps_load(&term->caps);
	if (tcsetattr(0, 0, &s_termios) == -1)
		return (-1);
	return (0);
}
