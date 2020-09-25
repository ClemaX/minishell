/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 15:51:38 by chamada           #+#    #+#             */
/*   Updated: 2020/09/25 14:29:23 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <term/term.h>
#include <abstract_dict.h>
#include <lexer.h>

void	print_abstract_dict(t_op *head)
{
	while (head && head->type)
	{
		// simplyfied version, can t print complex abstract dicts
		ft_printf("<print_abstract_dict> HEAD ADDR IS: %p\n", (t_op *)head);
		ft_printf("<print_abstract_dict> HEAD TYPE IS: %d\n", ((t_op *)head)->type);
		if (head->ch1)
		{
			ft_printf("<print_abstract_dict> GOES TO CH1\n");
			head = (t_op *)head->ch1;
		}
		else
			head = head->next;
	}
}

void	token_print(t_token *tokens)
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

int		exec(const char *str, t_term *t)
{
	t_token	*tokens;
	t_token	*operators;
	t_op	*head;

	if (*str == '\0')
		return (0);
	//ft_dprintf(2, "Input: %s\n", str);
	if(!lexer_tokenize(str, &tokens, &operators)
	|| !(head = malloc(sizeof(*head))))
	{
		ft_dprintf(2, "Error\n");
		return (-1);
	}
	token_print(tokens);
	token_print(operators);
	head->type = 0;
	head->back = NULL;
	(void)gen_architecture(operators, head);
	//print_abstract_dict(head);
	(void)gen_sub_architecture(tokens, head);
	tcsetattr(0, 0, &t->s_ios_bkp);
	(void)execute_abstract_dict(head, t);
	tcsetattr(0, 0, &t->s_ios);
	token_clear(&tokens);
	token_clear(&operators);
	(void)free_abstract_dict(head);
	return (0);
}

int		main(int ac, const char **av, const char **envp)
{
	return (term_prompt(ac, av, envp, &exec));
}
