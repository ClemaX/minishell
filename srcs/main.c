#include <ft_term.h>
#include <abstract_dict.h>
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
	t_op	*head;

	ft_dprintf(2, "Input: %s\n", str);
	if(!lexer_tokenize(str, &tokens, &operators)
	|| !(head = malloc(sizeof(*head))))
	{
		ft_dprintf(2, "Error\n");
		return (-1);
	}
	token_print(tokens);
	token_print(operators);


	(void)gen_architecture(operators, head);
	(void)gen_sub_architecture(tokens, head);
	(void)free_abstract_dict(head);

	token_clear(&tokens);
	token_clear(&operators);

	return (0);
}

int					main(int ac, const char **av, const char **envp)
{
	return (term_prompt(ac, av, envp, &exec));
}
