/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_tests.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 21:13:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 19:27:07 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <line.h>
#include <stdlib.h>
#include <libft.h>

static int	test_line_insert_at(void)
{
	t_line	*line;
	char	*str;

	line = NULL;
	line_insert_at(&line, 0, "TEST");
	ft_printf("%s\n", str = line_cat(&line, 0));
	free(str);
	line_insert_at(&line, 1, "AB");
	ft_printf("%s\n", str = line_cat(&line, 1));
	free(str);
	return (0);
}

int			line_test(int ac, const char **av, const char **ep)
{
	(void)ac;
	(void)av;
	(void)ep;
	test_line_insert_at();
	return (0);
}
