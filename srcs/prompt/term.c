/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   term.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:32:43 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 22:55:30 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <term.h>
#include <stdlib.h>

int	caps_get(t_caps *caps, char *term_type)
{
	if (term_type && (tgetent(NULL, term_type) > 0))
	{
		caps->cl = tgetstr("cm", NULL);
		caps->cl = tgetstr("ho", NULL);
		caps->cl = tgetstr("cl", NULL);
		caps->cl = tgetstr("ku", NULL);
		caps->cl = tgetstr("kd", NULL);
		caps->cl = tgetstr("kl", NULL);
		caps->cl = tgetstr("kr", NULL);
		return (1);
	}
	return (0);
}
