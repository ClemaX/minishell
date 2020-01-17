/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:46:56 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 22:59:52 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "tests.h"
#include <map.h>
#include <libft.h>
#include <env.h>
#include <stdlib.h>

int	main(int ac, const char **av, const char **ep)
{
	char	*str;

	map_test(ac, av, ep);
	path_test(ep);
	ft_asprintf(&str, "TEST: %s", "WOW");
	ft_printf("%s\n", str);
	free(str);
	return (0);
}
