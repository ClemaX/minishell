/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 11:12:18 by chamada     ###    #+. /#+    ###.fr     */
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

static void	print_tree(t_node *btree)
{
	if (btree)
	{
		if (btree->type == NODE_CMD)
			ft_printf("[CMD]: %s\n", btree->data);
		else if (btree->type == NODE_ARG)
			ft_printf("[ARG]: %s\n", btree->data);
		else if (btree->type == NODE_R_IN)
			ft_printf("[RIN]: %s\n", btree->data);
		else
			ft_printf("[%d]: %s\n", btree->type, btree->data);
		print_tree(btree->ch1);
		print_tree(btree->ch2);
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
//		print_tree(tree);
		cmd_line_execution(tree, env, name);
	}
	return (NULL);
}
