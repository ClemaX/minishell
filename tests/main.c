/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:46:56 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 06:45:17 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tests.h"
#include <map.h>
#include <libft.h>
#include <env.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>

typedef struct 	s_cursor
{
	int	x;
	int	y;
}				t_cursor;


int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	tc_test(const char **ep)
{
	t_map	*env;
	char	*term_type;
	char	*cl_cap;

	env = map_load(ep);
	term_type = map_get(env, "TERM")->value;
	tgetent(NULL, term_type);
	ft_printf("TERM=%s\n", term_type);
	cl_cap = tgetstr("cl", NULL);
	tputs(cl_cap, 1, &ft_putchar);
	map_clr(&env);
	return (0);
}

#include <lexer.h>

void	print_tokens(t_token *token)
{
	if (token)
	{
		print_tokens(token->next);
		ft_printf("%s\n", token->data);
		ft_printf("---------------------------------------------\n");
	}
}

char	*lexer_test(void)
{
	char	*line;
	char	*l;
	t_token	*tokens;

	while (*(line = line_read(0)))
	{
		tokens = line_tokenize(line);
		print_tokens(tokens);
		process_tokens(tokens);
		free(line);
	}
	return (line);
}

int	main(int ac, const char **av, const char **ep)
{
	char	*str;

	lexer_test();
	return (0);
}

/*
** map_test(ac, av, ep);
** path_test(ep);
** ft_asprintf(&str, "TEST: %s", "WOW");
** ft_printf("%s\n", str);
** free(str);
** tc_test(ep);
*/