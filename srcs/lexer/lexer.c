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
		&& !token_add(&tokens, token_new(
			ft_substr(start, 0, input - start), TOK_TOKEN)))
			return (token_clear(&tokens));
		if (status & LEX_OP)
		{
			if (!(token_add(&tokens, parse_token(&input))))
				return (NULL);
			status &= ~LEX_OP;
		}
	}
	return (tokens);
}
