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

int			lexer_tokenize(const char *input, t_token **tokens,
	t_token **operators)
{
	t_token_t	status;
	const char	*start;

	*tokens = NULL;
	*operators = NULL;
	ft_printf("[input is %s]\n", input);
	while (*input)
	{
		status = LEX_TOKEN;
		while (ft_isspace(*input))
			input++;
		start = input;
		while (*input && (status = lex_type(status, *input)) & LEX_TOKEN)
			input++;
		if (input != start)
		{
			if (!token_add(tokens, token_new(
				ft_substr(start, 0, input - start), TOK_TOKEN)))
			{
				token_clear(tokens);
				token_clear(operators);
				return (0);
			}
		}
		if (status & LEX_OP)
		{
			if (!token_add(operators, parse_token(&input))
			|| !token_add(tokens, token_new(ft_strdup(""), TOK_OP)))
			{
				token_clear(tokens);
				token_clear(operators);
				return (0);
			}
			status &= ~LEX_OP;
		}
	}
	if (!*operators && !(*operators = token_new(ft_strdup(""), 512))) // type none
	{
		token_clear(tokens);
		token_clear(operators);
		return (0);
	}
	ft_printf("[addr of op: %p]\n", *operators);
	ft_printf("[addr of data: %p]\n", *tokens);
	return (1);
}
