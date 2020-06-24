#include <lexer.h>

size_t		token_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

const char	**token_tab(t_token *tokens, int *n)
{
	const int	count = token_count(tokens);
	const char	**tab;
	t_token		*next;

	if (!(tab = malloc(sizeof(*tab) * (count + 1))))
		return (NULL);
	*n = 0;
	while (tokens)
	{
		next = tokens->next;
		tab[(*n)++] = tokens->data;
		free(tokens);
		tokens = next;
	}
	return (tab);
}

t_token		*token_next_cmd(t_token **tokens)
{
	t_token	*start;
	t_token *next;

	if ((start = *tokens))
	{
		while ((next = (*tokens)->next) && next->type == TOK_TOKEN)
			*tokens = next;
		if (next)
		{
			(*tokens)->next = NULL;
			*tokens = next->next;
		}
	}
	return (start);
}
