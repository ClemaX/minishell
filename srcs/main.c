#include <ft_term.h>
#include <lexer.h>

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

int exec(const char *str)
{
    t_token *tokens;
    ft_printf("Input: %s", str);
    tokens = lexer_tokenize(str);
    token_print(tokens);
    return (0);
}

int	main(int ac, const char **av, const char **envp)
{
	int		    ret;
	(void)	    ac;
	(void)	    av;

	ret = term_init(envp);
	if (ret == -1)
		return (ret);
	ret = term_prompt(&exec);
	return (ret);
}
