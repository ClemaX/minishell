/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arguments.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 10:17:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 14:14:55 by chamada     ###    #+. /#+    ###.fr     */
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
	if (status == 0 || status == EQUAL)
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

static t_status		status_handler(t_cmd *cmd, t_line **arg, char **line, t_status status)
{
	int	i;

	if (status & QUOTE && status & EQUAL)
	{
		line_add(arg, ft_strdup("="), 1);
		status &= ~EQUAL;
	}
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
	else if (status & DOLLAR)
	{
		if (ft_strncmp(*line, "$?", 3))
		{
			line_add(arg, ft_itoa(cmd->ret), ft_numlen(cmd->ret, 10));
			(*line)++;
		}
		status &= ~DOLLAR;
	}
	else if (status == EQUAL)
	{
		i = 0;
		while (i < (int)(*arg)->size &&
		(ft_isalnum(((*arg)->content[i])) || (*arg)->content[i] == '_'))
			i++;
		if (i != (int)(*arg)->size)
			status &= ~EQUAL;
	}
	return (status);
}

t_status			arg_parse(t_cmd *cmd, t_line **arg, char **line,
	t_status status)
{
	int	len;

	while (**line
	&& (((status ^= meta_parse(line)) & QUOTE) || !ft_isspace(**line)))
	{
		status = status_handler(cmd, arg, line, status);
		len = get_len(*line, status);
		line_add(arg, ft_substr(*line, 0, len), len);
		(*line) += len;
	}
	if (status & QUOTE)
		line_add(arg, ft_strdup("\n"), 1);
	if (status & EQUAL)
	{
		ft_printf("%s=%s\n", (*arg)->content, (*arg)->next->content);
		status &= ~EQUAL;
		line_clr(arg);
	}
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
