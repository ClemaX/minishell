/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer_test.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:01:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 05:41:13 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <map.h>
#include <lexer.h>
#include <stdlib.h>
#include <libft.h>

int	var_assign_test(void)
{
	t_token	token;
	t_map	*env;
	int		diff;

	if (!(token.data = ft_strdup("key=value")))
		error();
	env = NULL;
	token.type = TOKEN;
	if (var_assign(&token, &env) == -1)
		error();
	diff = diff_s(env->key, "key");
	diff += diff_s(env->value, "value");
	diff += diff_p(env->next, NULL);
	map_clr(&env);
	free(token.data);
	return (!diff);
}

int	var_expand_test(void)
{
	t_token	token;
	t_map	*env;
	int		diff;

	env = NULL;
	token.data = NULL;
	if (!(map_set(&env, "key", "value"))
	|| !(token.data = ft_strdup("$key"))
	|| var_expand(&token, &env) == -1)
	{
		map_clr(&env);
		free(token.data);
		error();
	}
	diff = diff_s(token.data, "value");
	map_clr(&env);
	free(token.data);
	return (!diff);
}

int	tilde_expand_test(void)
{
	t_token	token;
	t_map	*env;
	int		diff;

	if (!(token.data = ft_strdup("~/dir")))
		error();
	env = NULL;
	if (!(map_set(&env, "HOME", "/home")))
	{
		free(token.data);
		error();
	}
	tilde_expand(&token, &env);
	diff = diff_s(token.data, "/home/dir");
	map_clr(&env);
	free(token.data);
	return (!diff);
}

int	lexer_test(void)
{
	static const int	fw = 0;

	ft_printf(TITLE"Lexer\n"RESET);
	run_test("var_assign", fw, &var_assign_test);
	run_test("var_expand", fw, &var_expand_test);
	run_test("tilde_expand", fw, &tilde_expand_test);
	return (0);
}
