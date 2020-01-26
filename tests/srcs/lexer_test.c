/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 15:59:07 by chamada     ###    #+. /#+    ###.fr     */
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
		ft_printf("%s;", tokens->data);
		tokens = tokens->next;
	}
}

char	*lexer_test(int ac, const char **av, const char **ep)
{
	t_token		*tokens;
	t_map		*env;
	t_node		*tree;
	static t_term		term;
	char		*term_type;
	char		*line;
	t_line		*parsed;

	(void)ac;
	parsed = NULL;
	sig_init(&term);
	term.history = NULL;
	env = map_load(ep);
	term_type = map_get(env, "TERM")->value;
	term_init(&term, term_type);
	while ((prompt(&term)))
	{
		ft_printf("\n");
		line = line_parse(line_cat(&term.line->line, 0));
		tokens = line_tokenize(line);
		token_foreach(tokens, &env, &set_token_type_op);
		token_foreach(tokens, &env, &var_expand);
		token_foreach(tokens, &env, &var_assign);
		tree = cmd_line(&tokens);
		cmd_line_execution(tree, env, (char*)av[0]);
	}
	ft_printf("exit\n");
	return (0);
}
