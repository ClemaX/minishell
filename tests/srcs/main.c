/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:46:56 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 01:23:44 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>

int	main(int ac, const char **av, const char **ep)
{
	(void)ac;
	(void)av;
	(void)ep;
	lexer_test();
	prompt_test();
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