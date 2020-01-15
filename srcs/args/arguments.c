/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arguments.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 10:17:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 19:11:27 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

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
		while (line[len] &&
		(line[len] == '\'' || ft_strpos(META, line[len]) == -1))
			len++;
	return (len);
}

static t_status		status_handler(t_cmd *cmd, t_line **arg, char **line, t_status status)
{
	int		len;
	t_map	*var;

	if (status & QUOTE && status & EQUAL)
		status &= ~EQUAL;
	if (status & B_SLASH)
	{
		if (*(*line)++)
		{
			line_add(arg, ft_substr((*line)++, 0, 1), 1);
			status &= ~B_SLASH;
		}
		else
			line_add(arg, ft_strdup("\n"), 1);
	}
	else if (status & DOLLAR)
	{
		(*line)++;
		if (**line == '?')
		{
			line_add(arg, ft_itoa(cmd->ret), ft_numlen(cmd->ret, 10));
			(*line)++;
		}
		else
		{
			len = 0;
			while (ft_isalnum((*line)[len]) || (*line)[len] == '_')
				len++;
			if ((var = map_get(cmd->env, ft_substr(*line, 0, len))))
				line_add(arg, ft_strdup(var->value), ft_strlen(var->value));
			else
				line_add(arg, ft_strdup(""), 0);
			(*line) += len;
		}
		status &= ~DOLLAR;
	}
	else if (status == EQUAL)
	{
		(*line)++;
		if ((int)(*arg)->size == 0 || !arg_check((*arg)->content))
			status &= ~EQUAL;
	}
	return (status);
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
			status ^= (1 << pos);
		status = status_handler(cmd, arg, line, status);
		len = get_len(*line, status);
		line_add(arg, ft_substr(*line, 0, len), len);
		(*line) += len;
	}
	if (status & QUOTE)
		line_add(arg, ft_strdup("\n"), 1);
	if (status & EQUAL)
	{
		if (cmd->ac == 0)
		{
			map_set(&cmd->env, (*arg)->next->content, (*arg)->content);
			ft_printf("%s=%s\n", (*arg)->next->content, (*arg)->content);
			line_clr(arg);
		}
		else
			*arg = line_cat(arg);
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
