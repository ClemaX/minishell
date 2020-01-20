/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arguments.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 10:17:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 09:57:33 by chamada     ###    #+. /#+    ###.fr     */
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
		while (line[len] && (line[len] == '\'' || line[len] == ';'
		|| ft_strpos(META, line[len]) == -1))
			len++;
	return (len);
}

#include <token.h>

t_token				*token_new(char *str, t_token_t type)
{
	t_token	*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	token->data = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_status			arg_parse(t_cmd *cmd, t_token **arg, char **line,
	t_status status)
{
	t_line	*tmp;
	int		len;
	int 	pos;

	tmp = NULL;
	while (**line
	&& (status & QUOTE || !ft_isspace(**line)))
	{
		if ((pos = ft_strpos(META, **line)) != -1)
		{
			if ((1 << pos) & QUOTE)
				(*line)++;
			status ^= (1 << pos);
		}
		status = status_handler(cmd, &tmp, line, status);
		len = get_len(*line, status);
		line_add(&tmp, ft_substr(*line, 0, len), len);
		(*line) += len;
	}
	if (status & QUOTE)
		line_add(&tmp, ft_strdup("\n"), 1);
	if (status & EQUAL)
	{
		map_set(&cmd->env, tmp->next->content, tmp->content);
		line_clr(&tmp);
		status &= ~EQUAL;
	}
	else
		*arg = token_new(line_cat(&tmp), TOKEN);
	return (status);
}

int					args_export(t_cmd *cmd, t_token *args)
{
	t_token	*curr;
	int		i;

	if (!(cmd->av = ft_calloc(cmd->ac + 1, sizeof(*cmd->av))))
		return (0);
	curr = args;
	i = cmd->ac;
	while (i--)
	{
		cmd->av[i] = curr->data;
		curr = curr->next;
	}
	return (1);
}
