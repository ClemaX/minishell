/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 05:33:15 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <lexer.h>
#include <libft.h>
#include <map.h>
#include <parser.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("%s;", tokens->data);
		tokens = tokens->next;
	}
}

char	*lexer_test(void)
{
	char	*line;
	t_token	*tokens;
	t_history	*history;
	t_map		*env;

	history = NULL;
	env = NULL;
	map_set(&env, "USER", "TEST");
	while ((line = prompt(&history)))
	{
		line = line_parse(line);
		tokens = line_tokenize(line);
		token_foreach(tokens, &env, &set_token_type_op);
		token_foreach(tokens, &env, &var_expand);
		token_foreach(tokens, &env, &var_assign);
		print_tokens(tokens);
		parse(tokens);
		ft_printf("\n");
	}
	return (NULL);
}
