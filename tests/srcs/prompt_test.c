/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt_test.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:00:45 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 17:46:04 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <prompt.h>
#include <map.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>

int			tc_test(const char **ep)
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
