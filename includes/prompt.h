/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:32:10 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 22:52:47 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

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
	t_cursor	cursor;
	t_caps		caps;
	t_history	*history;
}				t_term;

char			*prompt(t_history **history);

t_history		*history_add(t_history **history, char *line);
void			history_clr(t_history **history);

#endif