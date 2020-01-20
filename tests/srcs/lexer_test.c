/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:45:07 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <lexer.h>
#include <libft.h>
#include <map.h>

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_printf("%s ", tokens->data);
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
		line = line_read(line);
		tokens = line_tokenize(line);
		token_foreach(tokens, env, &var_expand);
		print_tokens(tokens);
		ft_printf("\n");
	}
	return (NULL);
}
