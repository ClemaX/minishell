/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:17:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 19:08:29 by chamada     ###    #+. /#+    ###.fr     */
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

char		*line_parse(char *str)
{
	t_line	*line;
	int		status;
	int		pos;
	char	c;

	line = NULL;
	status = 0;
	while ((c = *str++))
	{
		if ((status & S_QUOTES && c != '\'')
		|| (status & D_QUOTES && (c == '\'' || ft_strpos(META, c) == -1)))
		{
			line_add(&line, c);
			continue ;
		}
		if (status & B_SLASH)
		{
			line_add(&line, c);
			status &= ~B_SLASH;
			continue ;
		}
		if ((pos = ft_strpos(META, c)) != -1)
			status ^= (1 << pos);
		if (!(status & B_SLASH))
			line_add(&line, c);
	}
	return (line_cat(&line, 1));
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

