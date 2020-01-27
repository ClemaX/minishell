/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 21:15:05 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <global_var.h>
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>
#include <lexer.h>
#include <parser.h>
#include <map.h>
#include <prompt.h>
#include <execution.h>

int g_pid = 0;
/*static int	print_status(t_status status, t_cmd *cmd)
{
	if (status)
		ft_printf("> ");
	else
		ft_printf("%s>$ ", map_get(cmd->glob_env, "PWD")->value);
	return (1);
} */


t_map		*map_dup(t_map	*map)
{
	t_map	*curr;
	t_map	*dup;

	dup = NULL;
	curr = map;
	while (curr)
	{
		map_set(&dup, curr->key, curr->value);
		curr = curr->next;
	}
	return (dup);
}

int			main(int ac, char **av, const char **envp)
{
	t_token		*tokens;
	t_node		*tree;
	static t_term	term;
	char		*term_type;
	char		*line;
	t_line		*parsed;

	(void)ac;
	term.name = av[0];
	parsed = NULL;
	sig_init(&term);
	term.history = NULL;
	term.env = map_load(envp);
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
	return (1);
}
