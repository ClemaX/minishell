/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arguments.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 10:17:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 10:50:05 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <command.h>
#include <line.h>
#include <libft.h>
#include <stdlib.h>

static t_status		meta_parse(char **line)
{
	int			pos;

	if ((pos = ft_strpos(META, **line)) != -1)
	{
		(*line)++;
		return (1 << pos);
	}
	return (0);
}

static int			get_len(char *line, t_status status)
{
	int	len;

	len = 0;
	if (status == 0)
		while (line[len] && !ft_isspace(line[len])
			&& ft_strpos(META, line[len]) == -1)
			len++;
	else if (status & S_QUOTE)
		while (line[len] && line[len] != '\'')
			len++;
	else if (status & D_QUOTE)
		while (line[len] &&
		(line[len] == '\'' || ft_strpos(META, line[len]) == -1))
			len++;
	return (len);
}

static t_status		status_handler(t_line **arg, char **line, t_status status)
{
	if (status & B_SLASH)
	{
		if (**line)
		{
			line_add(arg, ft_substr((*line)++, 0, 1), 1);
			status &= ~B_SLASH;
		}
		else
			line_add(arg, ft_strdup("\n"), 1);
	}
	return (status);
}

t_status			arg_parse(t_line **arg, char **line, t_status status)
{
	int	len;

	while (**line
	&& (((status ^= meta_parse(line)) & QUOTE) || !ft_isspace(**line)))
	{
		status = status_handler(arg, line, status);
		len = get_len(*line, status);
		line_add(arg, ft_substr(*line, 0, len), len);
		(*line) += len;
	}
	if (status & QUOTE)
		line_add(arg, ft_strdup("\n"), 1);
	*arg = line_cat(arg);
	return (status);
}

int					args_export(t_cmd *cmd, t_line *args)
{
	t_line	*curr;
	int		i;

	curr = args;
	cmd->ac = 0;
	while (curr)
	{
		cmd->ac++;
		curr = curr->next;
	}
	if (!(cmd->av = ft_calloc(cmd->ac + 1, sizeof(*cmd->av))))
		return (0);
	curr = args;
	i = cmd->ac;
	while (i--)
	{
		cmd->av[i] = curr->content;
		curr = curr->next;
	}
	return (1);
}
