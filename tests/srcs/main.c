/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:46:56 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:03:03 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include "global_var.h"

g_pid = 0;

int	main(int ac, const char **av, const char **ep)
{
	(void)ac;
	lexer_test(av[0], ep);
	return (0);
}

/*
** map_test(ac, av, ep);
** path_test(ep);
** ft_asprintf(&str, "TEST: %s", "WOW");
** ft_printf("%s\n", str);
** free(str);
**	prompt_test();
** tc_test(ep);
*/