/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 18:29:56 by chamada     ###    #+. /#+    ###.fr     */
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

char	*lexer_test(char *name, const char **ep)
{
	char		*line;
	t_token		*tokens;
	t_map		*env;
	t_node		*tree;
	t_term		term;

	sig_init(&term);
	term.history = NULL;
	env = map_load(ep);
	term_init(&term, map_get(env, "TERM")->value);
	while ((line = prompt(&term)))
	{
		ft_printf("\n");
		line = line_parse(line);
		tokens = line_tokenize(line);
		token_foreach(tokens, &env, &set_token_type_op);
		token_foreach(tokens, &env, &var_expand);
		token_foreach(tokens, &env, &var_assign);
		tree = cmd_line(&tokens);
		cmd_line_execution(tree, env, name);
	}
	ft_printf("exit\n");
	return (NULL);
}
