/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:31:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 19:38:13 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <line.h>
#include <lexer.h>
#include <unistd.h>
#include <libft.h>
#include <stdlib.h>

static char	*char_dup(char c)
{
	char	*res;

	if (!(res = malloc(sizeof(char))))
		return (NULL);
	*res = c;
	return (res);
}

static int	handle_special(t_term *term, char c)
{
	if (c == '\004')
	{
		ft_printf("exit\n");
		exit(0);
	}
	else if (c == '\n')
	{
		ft_printf("> ");
		term->cursor.y++;
		term->cursor.x = 0;
	}
	else if (c == 27)
		caps_handler(term);
	else
		return (0);
	return (1);
}

char		*read_line(t_term *term)
{
	char	c;
	int		pos;
	int		ret;
	int		status;

	term->line = history_add(&term->history);
	status = 0;
	ft_printf("minish>$ ");
	while ((ret = read(STDIN_FILENO, &c, 1)) == 1
	&& (c != '\n' || status & WAITING))
	{
		if (!(handle_special(term, c)))
		{
			write(1, &c, 1);
			line_add(&term->line->line, char_dup(c), 1);
			term->cursor.x++;
			term->cursor.max.x++;
			if (!((status & S_QUOTES && c != '\'')
			|| (status & D_QUOTES && (c == '\'' || ft_strpos(META, c) == -1))))
			{
				if (status & B_SLASH)
					status &= ~B_SLASH;
				else if ((pos = ft_strpos(META, c)) != -1)
					status ^= (1 << pos);
			}
		}
	}
	if (ret != 1)
		return ((char*)line_clr(&term->line->line));
	return (line_cat(&term->line->line));
}

char		*prompt(t_term *term)
{
	t_line	*line;

	if (tcsetattr(0, 0, &term->s_termios) == -1
	|| !(line = read_line(term))
	|| tcsetattr(0, 0, &term->s_termios_bkp) == -1)
		return (NULL);
	term->cursor = (t_cursor){.x=0, .y=0, .max={.x=0, .y=0}};
	return (line);
}
