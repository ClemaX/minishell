/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 06:46:56 by chamada           #+#    #+#             */
/*   Updated: 2020/01/26 20:42:21 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <tests.h>
#include "global_var.h"

int g_pid = 0;

int	main(int ac, const char **av, const char **ep)
{
//	map_test(ac, av, ep);
//	line_test(ac, av, ep);
	lexer_test(ac, av, ep);
	return (0);
}

/*
** 
** path_test(ep);
** ft_asprintf(&str, "TEST: %s", "WOW");
** ft_printf("%s\n", str);
** free(str);
**	prompt_test();
** tc_test(ep);
*/