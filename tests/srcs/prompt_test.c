/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   prompt_test.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 22:00:45 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/19 22:55:58 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <prompt.h>
#include <map.h>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>

static int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

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

int			prompt_test(void)
{
	t_history	*hist;
	char		*line;

	hist = NULL;
	while ((line = prompt(&hist)))
		ft_printf("%s\n", line);
	history_clr(&hist);
	return (0);
}
