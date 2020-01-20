/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:17:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:48:18 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <lexer.h>
#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <line.h>

t_token	*token_add(t_token **tokens, char *data, t_token_t type)
{
	t_token	*last;
	t_token *new;

	if (!data || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->type = type;
	if (!*tokens)
		return (*tokens = new);
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}

static char	*char_dup(char c)
{
	char	*res;

	if (!(res = malloc(sizeof(char))))
		return (NULL);
	*res = c;
	return (res);
}
#include <map.h>
#include <command.h>

int	var_expand(t_token *token, void *env)
{
	char	*c;
	char	*join;
	t_map	*var;

	ft_printf("%s", token->data);
	if ((c = ft_strchr(token->data, '$')) && key_check(c + 1))
	{
		*c = '\0';
		if ((var = map_get((t_map*)env, c + 1)))
		{
			if (!(join = ft_strjoin(token->data, var->value)))
				return (-1);
			free(token->data);
			token->data = join;
		}
		return (1);
	}
	return (0);
}

int	token_foreach(t_token *tokens, void *env, int (f)(t_token*, void*))
{
	t_token	*curr;
	int		ret;

	curr = tokens;
	ret = 0;
	while (curr && (ret = f(curr, env)) != -1)
		curr = curr->next;
	return (ret == -1 ? -1 : 1);
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

char	*line_read(char *str)
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
