/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arguments.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 10:17:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 20:17:42 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


/* not multiline with unfinished quotes */

#include <command.h>
#include <line.h>
#include <libft.h>
#include <stdlib.h>

static int			get_len(char *line, t_status status)
{
	int	len;

	len = 0;
	if (status == 0 || status == EQUAL)
		while (line[len] && !ft_isspace(line[len])
			&& ft_strpos(META, line[len]) == -1)
			len++;
	else if (status & S_QUOTE)
		while (line[len] && line[len] != '\'')
			len++;
	else if (status & D_QUOTE)
		while (line[len] && (line[len] == '\'' || line[len] == ';'
		|| ft_strpos(META, line[len]) == -1))
			len++;
	return (len);
}

t_status			arg_parse(t_cmd *cmd, t_line **arg, char **line,
	t_status status)
{
	int	len;
	int pos;

	while (**line
	&& (status & QUOTE || !ft_isspace(**line)))
	{
		if ((pos = ft_strpos(META, **line)) != -1)
		{
			if ((1 << pos) & QUOTE)
				(*line)++;
			status ^= (1 << pos);
		}
		status = status_handler(cmd, arg, line, status);
		if (status & SEMICOL)
			return (status);
		len = get_len(*line, status);
		line_add(arg, ft_substr(*line, 0, len), len);
		(*line) += len;
	}
	if (status & QUOTE)
		line_add(arg, ft_strdup("\n"), 1);
	if (status & EQUAL)
	{
		map_set(&cmd->env, (*arg)->next->content, (*arg)->content);
		ft_printf("%s=%s\n", (*arg)->next->content, (*arg)->content);
		line_clr(arg);
		status &= ~EQUAL;
	}
	else
		*arg = line_cat(arg);
	return (status);
}

int					args_export(t_cmd *cmd, t_line *args)
{
	t_line	*curr;
	int		i;

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
