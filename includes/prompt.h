/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:32:10 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 23:15:54 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#ifndef PROMPT_H
# define PROMPT_H

# include <term.h>
# include <line.h>
# include <map.h>

# define COPY	19
# define CUT	24
# define PASTE	23
# define ENTER	10
# define MINUS	45

typedef struct	s_cursor
{
	int		x;
	int		y;
	struct
	{
		int x;
		int y;
	}		max;
}				t_cursor;

typedef struct	s_history
{
	t_line				*line;
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
	char	*le;
	char	*nd;
	char	*ce;
	char	*cr;
	char	*ch;
	char	*ec;
	char	*dc_n;
}				t_caps;

typedef struct	s_term
{
	t_cursor		cursor;
	t_caps			caps;
	t_history		*history;
	t_history		*line;
	t_map			*env;
	char			*name;
	struct termios	s_termios;
	struct termios	s_termios_bkp;
	char			*copy;
}				t_term;

t_line			*prompt(t_term *term);

t_history		*history_add(t_history **history);
void			history_clr(t_history **history);

int				term_init(t_term *term, const char *term_type);
int				caps_handler(t_term *term);

void			sig_handler(int sig, void *param);
void			sig_init(t_term *term);

void			cursor_del_range(t_term *term, int min, int max);

void			handle_cpy_and_cut(t_term *term, char signal, 
	int pos, char *(*x)(t_term *, int, int, int));
char       		*ft_copy(t_term *term, int pos, int dir, int size);
char            *ft_cut(t_term *term, int pos, int dir, int size);
void            ft_paste(t_term *term, int pos, char *to_paste);

int        		next_wd_right(char *line, int *pos);
int      		next_wd_left(char *line, int *pos);

#endif