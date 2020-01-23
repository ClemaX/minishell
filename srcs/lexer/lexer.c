/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:17:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 19:33:19 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <line.h>
#include <lexer.h>
#include <token.h>
#include <stdlib.h>
#include <libft.h>

static char	*char_dup(char c)
{
	char	*res;

	if (!(res = malloc(sizeof(char))))
		return (NULL);
	*res = c;
	return (res);
}

t_token		*line_tokenize(char *line)
{
	t_token	*tokens;
	char	*l;
	char	in_quotes;

	l = line;
	in_quotes = 0;
	tokens = NULL;
	while (*l)
	{
		while (ft_isspace(*l))
			l++;
		line = l;
		while (*l
		&& (in_quotes || ((*l == '\n' || !ft_isspace(*l)) && *l != ';')))
		{
			if (*l == '\'' || *l == '\"')
				in_quotes ^= *l == '\'' ? 1 : 2;
			l++;
		}
		if (l != line)
			token_add(&tokens, ft_substr(line, 0, l - line), TOKEN);
		if (*l == ';')
		{
			token_add(&tokens, ft_strdup(";"), TOKEN);
			l++;
		}
	}
	return (tokens);
}

char		*line_parse(t_line *line)
{
	t_line	*parsed;
	int		status;
	int		pos;

	parsed = NULL;
	status = 0;
	while (line)
	{
		if ((status & S_QUOTES && *line->content != '\'')
		|| (status & D_QUOTES && (*line->content == '\''
		|| ft_strpos(META, *line->content) == -1)))
			line_add(&parsed, char_dup(*line->content), 1);
		else if (status & B_SLASH)
		{
			line_add(&parsed, char_dup(*line->content), 1);
			status &= ~B_SLASH;
		}
		else
		{
			if ((pos = ft_strpos(META, *line->content)) != -1)
				status ^= (1 << pos);
			if (!(status & B_SLASH))
				line_add(&parsed, char_dup(*line->content), 1);
		}
		line = line->next;
	}
	return (line_cat(&parsed));
}

int		set_token_type_op(t_token *token, void *param)
{
	(void)param;
	if (!ft_strncmp("|", token->data, 2))
		token->type = OP_PIPE;
	else if (!ft_strncmp(";", token->data, 2))
		token->type = OP_SEMICOLON;
	else if (!ft_strncmp("&&", token->data, 3))
		token->type = OP_AND;
	else if (!ft_strncmp("<", token->data, 2))
		token->type = OP_LESSER;
	else if (!ft_strncmp(">", token->data, 2))
		token->type = OP_GREATER;
	else if (!ft_strncmp("||", token->data, 3))
		token->type = OP_OR;
	else
		return (0);
	return (1);
}

