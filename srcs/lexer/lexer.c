#include <lexer.h>

static int	lex_type(int status, char c)
{
	if (status & LEX_B_SLASH)
		return (status & ~LEX_B_SLASH);
	if (status & LEX_S_QUOTE && c != '\'')
		return (status);
	if (c == '"')
		return (status ^ LEX_D_QUOTE);
	if (!(status & LEX_D_QUOTE))
	{
		if (c == '\'')
			return (status ^ LEX_S_QUOTE);
		if (ft_isspace(c))
			return (status & ~LEX_TOKEN);
		if (c == '\\')
			return (status | LEX_B_SLASH);
		if (ft_strchr(OPERATORS, c))
			return ((status & ~LEX_TOKEN) | LEX_OP);
	}
	return (status);
}

t_token		*token_add(t_token **tokens, char *data, t_token_t type)
{
	t_token	*new;
	t_token	*curr;

	if (!data || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->data = data;
	new->type = type;
	new->next = NULL;
	if (*tokens)
	{
		curr = *tokens;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	else
		*tokens = new;
	return (new);
}

t_token		*token_clear(t_token **token)
{
	t_token	*next;

	while (*token)
	{
		next = (*token)->next;
		free((*token)->data);
		free(*token);
		*token = next;
	}
	return (*token);
}

t_token		*lexer_tokenize(const char *input)
{
	t_token_t	status;
	const char	*start;
	t_token		*tokens;

	tokens = NULL;
	while (*input)
	{
		status = LEX_TOKEN;
		while (ft_isspace(*input))
			input++;
		start = input;
		while (*input && (status = lex_type(status, *input)) & LEX_TOKEN)
			input++;
		if (input != start
		&& !token_add(&tokens, ft_substr(start, 0, input - start), TOK_TOKEN))
			return (token_clear(&tokens));
		if (status & LEX_OP)
		{
			ft_printf("TODO: Operator");
			status &= ~LEX_OP;
		}
	}
	return (tokens);
}

void		token_print(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("(%d)[%s]", tokens->type, tokens->data);
		tokens = tokens->next;
		if (tokens)
			ft_printf(", ");
	}
}

int			lexer_test(void)
{
	static const char	*str = "Hello world!";
	t_token				*tokens;

	tokens = lexer_tokenize(str);
	token_print(tokens);
	return (0);
}
