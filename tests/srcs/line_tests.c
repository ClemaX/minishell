/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_tests.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 21:13:22 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:11:07 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <line.h>
#include <stdlib.h>
#include <libft.h>

static int	line_insert_at_test(void)
{
	static const int	len = 10;
	const int			pos = ft_rand(1, 4);
	t_line				*line;
	char				expected[32];
	char				*tmp;

	line = NULL;
	ft_strlcpy(expected, tmp = rand_val(len), len + 1);
	line_insert_at(&line, 0, tmp);
	free(tmp);
	diff_s(tmp = line_cat(&line, 0), expected);
	free(tmp);
	ft_memmove(expected + pos + len, expected + pos, len - pos + 1);
	ft_memcpy(expected + pos, tmp = rand_val(len), len);
	line_insert_at(&line, pos, tmp);
	free(tmp);
	if (diff_s(tmp = line_cat(&line, 1), expected))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static int	line_add_test(void)
{
	static const char	*expected = "TEST";
	const char			*i = expected;
	t_line				*line;
	char				*tmp;

	line = NULL;
	while (*i)
		line_add(&line, *i++);
	if (diff_s(tmp = line_cat(&line, 1), (char *)expected))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int			line_test(void)
{
	static const int	fw = -14;

	ft_printf(TITLE"Line\n"RESET);
	run_test("line_add", fw, &line_add_test);
	run_test("line_insert_at", fw, &line_insert_at_test);
	return (0);
}
