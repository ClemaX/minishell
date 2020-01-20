/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:31:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 01:22:06 by chamada     ###    #+. /#+    ###.fr     */
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

char		*read_line(void)
{
	char	c;
	int		pos;
	int		ret;
	t_line	*line;
	int		status;

	line = NULL;
	status = 0;
	while ((ret = read(STDIN_FILENO, &c, 1)) == 1
	&& (c != '\n' || status & WAITING))
	{
		line_add(&line, char_dup(c), 1);
		if (!((status & S_QUOTES && c != '\'')
		|| (status & D_QUOTES && c != '"')))
		{
			if (status & B_SLASH)
				status &= ~B_SLASH;
			else if ((pos = ft_strpos(META, c)) != -1)
				status ^= (1 << pos);
		}
	}
	if (ret != 1)
		return ((char*)line_clr(&line));
	return (line_cat(&line));
}

char		*prompt(t_history **history)
{
	char	*line;

	if (!(line = read_line()))
		return (NULL);
	return (history_add(history, line)->line);
}
