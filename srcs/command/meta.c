/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   meta.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 20:17:32 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 20:26:40 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <command.h>

static t_status	handle_b_slash(t_line **arg, char **line, t_status status)
{
	if (*(*line)++)
	{
		line_add(arg, ft_substr((*line)++, 0, 1), 1);
		status &= ~B_SLASH;
	}
	else
		line_add(arg, ft_strdup("\n"), 1);
	return (status);
}

static t_status	handle_dollar(t_cmd *cmd, t_line **arg, char **line,
	t_status status)
{
	t_map	*var;
	int		len;

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
			line_add(arg, NULL, 0);
		(*line) += len;
	}
	return (status & ~DOLLAR);
}

static t_status	handle_equal(t_cmd *cmd, t_line **arg, char **line,
	t_status status)
{
	(*line)++;
	if (cmd->ac != 0 || !*arg || (int)(*arg)->size == 0
	|| !arg_check((*arg)->content))
	{
		status &= ~EQUAL;
		line_add(arg, ft_strdup("="), 1);
	}
	return (status);
}

t_status		status_handler(t_cmd *cmd, t_line **arg, char **line,
	t_status status)
{
	if (status & QUOTE)
		status &= ~(EQUAL | SEMICOL);
	else if (status & SEMICOL)
		(*line)++;
	if (status & B_SLASH)
		status = handle_b_slash(arg, line, status);
	else if (status & DOLLAR)
		status = handle_dollar(cmd, arg, line, status);
	else if (status == EQUAL)
		status = handle_equal(cmd, arg, line, status);
	return (status);
}
