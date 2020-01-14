/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 05:20:02 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


/* 
TO DO : ESCAPABLE CHARS FCT
*/



#include <command.h>
#include <libft.h>
#include <line.h>

#include <stdlib.h>

void		parse_content(t_line **arg, char **line, t_status status)
{
	int		len;
	char	*content;
	char	*end;

	if (!*line)
		return ;
	len = 0;
	end = NULL;
	if (status & S_QUOTE)
		end = ft_strchr(*line, '\'');
	if (end)
		len = end - *line;
	else
		while ((*line)[len] && ft_strpos(status & D_QUOTE ? "\"\"\\" : S_CHAR, (*line)[len]) == -1)
			len++;
	if (!len || !(content = malloc(sizeof(*content) * len)))
		return ;
	ft_memcpy(content, *line, len);
	line_add(arg, content, len);
	*line += len;
}

t_status	parse_status(char **line, t_line **arg, t_status status)
{
	int			pos;

	while (**line && 
	(pos = ft_strpos(status & D_QUOTE ? "\"\"\\" : S_CHAR, **line)) != -1)
	{
		(*line)++;
		status ^= (1 << pos);
		if (status & BACKSLASH)
		{
			line_add(arg, (*line)++, 1);
			status &= ~BACKSLASH;
		}
		else if (status & S_QUOTE && !(status & D_QUOTE))
			return (status);
	}
	return (status);
}

#include <unistd.h>

void		line_cat(t_line *line)
{
	t_line	*current;

	current = line;
	while (current)
	{
		write(1, current->content, current->size);
		write(1, "\n", 1);
		current = current->next;
	}
}

t_status		parse_cmd(t_status status, t_cmd *cmd, char *line)
{
	t_line		*args;
	t_line		*arg;
	char		*start;

	(void)args;
	(void)cmd;
	arg = NULL;
	while (ft_isspace(*line))
		line++;
	while (*(start = line)
	&& ((status = parse_status(&line, &arg, status)) & (D_QUOTE | S_QUOTE)
	|| !ft_isspace(*line)))
	{
		parse_content(&arg, &line, status);
	}
	line_cat(arg);
	return (status);
}
