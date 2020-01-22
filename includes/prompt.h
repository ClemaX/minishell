/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:32:10 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 12:12:57 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <term.h>

typedef struct	s_cursor
{
	int	x;
	int	y;
}				t_cursor;

typedef struct	s_history
{
	char				*line;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

/*
**	cursor move
**	home
**	clear screen
**	key up
**	key down
**	key left
**	key right
*/

typedef struct	s_caps
{
	char	*cm;
	char	*ho;
	char	*cl;
	char	*ku;
	char	*kd;
	char	*kl;
	char	*kr;
}				t_caps;

typedef struct	s_term
{
	t_cursor		cursor;
	t_caps			caps;
	t_history		*history;
	struct termios	s_termios_bkp;
}				t_term;

char			*prompt(t_history **history);

t_history		*history_add(t_history **history, char *line);
void			history_clr(t_history **history);

int				term_init(t_term *term, const char *term_type);
int				caps_handler(t_term *term);

void			sig_handler(int sig);
void			sig_init(void);

#endif