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

int	main(int ac, const char **av, const char **ep)
{
	map_test(ac, av, ep);
	path_test(ep);
	return (0);
}
