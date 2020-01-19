/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:17:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 06:43:38 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <lexer.h>
#include <unistd.h>
#include <libft.h>
#include <line.h>

#define META		"\"\'\\()"

#define D_QUOTES	1
#define S_QUOTES	2
#define B_SLASH		4
#define PARENTH_IN	8
#define PARENTH_OUT	16

#define WAITING		15

t_token	*token_add(t_token **tokens, char *data, t_token_t type)
{
	t_token *new;

	if (!data || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->data = data;
	new->next = *tokens;
	new->type = type;
	return ((*tokens = new));
}

char	*char_dup(char c)
{
	char	*res;

	if (!(res = malloc(sizeof(char))))
		return (NULL);
	*res = c;
	return (res);
}

t_token	*line_tokenize(char *line)
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
		while (*l && (in_quotes || !ft_isspace(*l)))
		{
			if (*l == '\'' || *l == '\"')
				in_quotes ^= *l == '\'' ? 1 : 2;
			l++;
		}
		token_add(&tokens, ft_substr(line, 0, l - line), TOKEN);
	}
	return (tokens);
}

char	*line_read(int fd)
{
	t_line	*line;
	int		status;
	int		pos;
	char	c;

	line = NULL;
	status = 0;
	while (read(fd, &c, 1) == 1 && (c != '\n' || status & WAITING))
	{
		if ((status & S_QUOTES && c != '\'')
		|| (status & D_QUOTES && c != '"'))
		{
			line_add(&line, char_dup(c), 1);
			continue ;
		}
		else if (status & B_SLASH)
		{
			line_add(&line, char_dup(c), 1);
			status &= ~B_SLASH;
			continue ;
		}
		if ((pos = ft_strpos(META, c)) != -1)
			status ^= (1 << pos);
		if (!(status & B_SLASH))
			line_add(&line, char_dup(c), 1);
	}
	return (line_cat(&line));
}
