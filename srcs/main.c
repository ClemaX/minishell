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
	t_token	*tokens;
	t_token	*operators;

	ft_dprintf(2, "Input: %s\n", str);
	if(!lexer_tokenize(str, &tokens, &operators))
	{
		ft_dprintf(2, "Error\n");
		return (-1);
	}
	token_print(tokens);
	token_print(operators);
	token_clear(&tokens);
	token_clear(&operators);

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
