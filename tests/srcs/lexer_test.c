/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 03:39:16 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <lexer.h>
#include <libft.h>
#include <map.h>
#include <parser.h>
#include <execution.h>
#include <signal.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		//ft_printf("%s;", tokens->data);
		tokens = tokens->next;
	}
}

char	*lexer_test(int ac, char **av, const char **ep)
{
	t_token	*tokens;
	t_node	*tree;
	t_term	term;
	char	*term_type;
	char	*line;
	t_line	*parsed;

	(void)ac;
	term.name = av[0];
	parsed = NULL;
	sig_init(&term);
	term.history = NULL;
	term.env = map_load(ep);
	term_type = map_get(term.env, "TERM")->value;
	term_init(&term, term_type);
	while ((prompt(&term)))
	{
		ft_printf("\n");
		line = line_parse(line_cat(&term.line, 0));
		term.line = NULL;
		tokens = line_tokenize(line);
		token_foreach(tokens, &term.env, &set_token_type_op);
		token_foreach(tokens, &term.env, &var_expand);
		token_foreach(tokens, &term.env, &var_assign);
		tree = cmd_line(&tokens);
		cmd_line_execution(tree, &term);
	}
	ft_printf("exit\n");
	return (0);
}
