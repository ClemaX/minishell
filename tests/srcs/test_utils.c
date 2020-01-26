/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 16:34:23 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 19:33:04 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <libft.h>
#include <stdlib.h>

int		diff_s(const char *got, const char *expected)
{
	int	diff;

	if ((diff = ft_strcmp(got, expected)))
		ft_printf("%s: got: %s, expected: %s\n",
			RED"DIFF"RESET, got, expected);
	return (diff);
}

int		diff_p(const void *got, const void *expected)
{
	if (got != expected)
	{
		ft_printf("%s: got: %p, expected: %p\n",
			RED"DIFF"RESET, got, expected);
		return (1);
	}
	return (0);
}

int		run_test(const char *label, int fw, int (*test)())
{
	int	ret;

	ft_printf("%s %*s %s\n",
		BULLET, fw, label, (ret = (*test)()) ? PASS : FAIL);
	return (ret);
}
