/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:46:56 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:28:03 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include "global_var.h"

int g_pid = 0;

int	main(void)
{
	line_test();
	map_test();
	path_test();
//	lexer_test(ac, av, ep);
	return (0);
}

/*
**	ft_asprintf(&str, "TEST: %s", "WOW");
**	ft_printf("%s\n", str);
**	free(str);
**	prompt_test();
**	tc_test(ep);
*/