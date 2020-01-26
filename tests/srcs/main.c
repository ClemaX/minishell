/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 06:46:56 by chamada           #+#    #+#             */
/*   Updated: 2020/01/26 21:54:27 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <tests.h>
#include "global_var.h"

int g_pid = 0;

int	main(void)
{
//	map_test(ac, av, ep);
//	line_test(ac, av, ep);
	lexer_test();
	return (0);
}

/*
**	ft_asprintf(&str, "TEST: %s", "WOW");
**	ft_printf("%s\n", str);
**	free(str);
**	prompt_test();
**	tc_test(ep);
*/