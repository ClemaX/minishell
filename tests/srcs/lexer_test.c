/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 07:47:25 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <lexer.h>
#include <libft.h>
#include <map.h>
#include <parser.h>
#include <execution.h>

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
	t_history	*history;
	t_map		*env;
	t_node		*tree;

	history = NULL;
	env = map_load(ep);
	while ((line = prompt(&history)))
	{
		line = line_parse(line);
		tokens = line_tokenize(line);
		token_foreach(tokens, &env, &set_token_type_op);
		token_foreach(tokens, &env, &var_expand);
		token_foreach(tokens, &env, &var_assign);
		tree = cmd_line(&tokens);
		cmd_line_execution(tree, env, name);
	}
	return (NULL);
}
