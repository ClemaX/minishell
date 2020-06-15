#include <ft_term.h>
#include <lexer.h>

void		token_print(t_token *tokens)
{
	while (tokens)
	{
		ft_dprintf(2, "(%d)[%s]", tokens->type, tokens->data);
		tokens = tokens->next;
		if (tokens)
			ft_dprintf(2, ", ");
	}
	ft_dprintf(2, "\n");
}

int exec(const char *str)
{
	t_token *tokens;

	ft_dprintf(2, "Input: %s\n", str);
	tokens = lexer_tokenize(str);
	token_print(tokens);
	token_clear(&tokens);
	return (0);
}

int	main(int ac, const char **av, const char **envp)
{
	int		ret;
	(void)	ac;
	(void)	av;

	ret = term_prompt(envp, &exec);
	return (ret);
}
