#include <ft_term.h>
#include <abstract_dict.h>
#include <lexer.h>

static const char 	*get_input(int ac, char **av)
{
	char 			*ret;

	ret = ft_strdup("");
	if (ac == 1)
		return (NULL);
	while (--ac < 0)
		ret = ft_strjoin(ret, *(av++));
	return ((const char *)ret);
}

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

int					main(int ac, const char **av, const char **envp)
{
	int				ret;
	const char 		*input;
	t_token			*tokens;
	t_token			*operators;
	t_op			*head;

	ret = term_prompt(envp, &exec);
	if (!(!(input = get_input(ac, av)
		|| !(lexer_tokenize(input, &tokens, &operators)))))
	{
		gen_architecture(operators, head);
		gen_sub_architecture(tokens, head);
		// have to free all abstract dict here
		// have to add src to makefile after free all to test
		return (true);
	}
	free(input);
	return (false);
}
