/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/12 06:30:25 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <command.h>
#include <libft.h>
#include <printf/line.h>

t_status	parse_status(char **line)
{
	int			pos;
	t_status	status;

	while ((pos = ft_strpos(S_CHAR, **line)) != -1)
	{
		(*line)++;
		status ^= (1 << pos);
		if (status & BACKSLASH)
			return (status);
	}
	return (status);
}

t_status	parse_backslash(t_status status, t_line *arg, char **line)
{
	while (status & BACKSLASH)
	{
		line_add(&arg, line++, 1);
		status &= ~BACKSLASH;
		status ^= parse_status(&line);
	}
	return (status);
}

void		parse_cmd(t_cmd *cmd, char *line)
{
	t_status	status;
	t_line		*arg;
	char		*start;

	while (ft_isspace(*line))
		line++;
	status = parse_status(&line) ^ parse_backslash(status, arg, line);
	while (status & QUOTE)
	{
		status ^= parse_status(&line);
	}
}
