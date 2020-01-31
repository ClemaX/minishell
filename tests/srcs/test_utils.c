/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 16:34:23 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 21:47:56 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <tests.h>
#include <libft.h>
#include <stdlib.h>

int		diff_s(char *got, char *expected)
{
	int	diff;

	if ((diff = ft_strcmp(got, expected)))
		ft_printf("%s: got: %s, expected: %s\n",
			RED"DIFF"RESET, got, expected);
	return (diff != 0);
}

int		diff_p(void *got, void *expected)
{
	if (got != expected)
	{
		ft_printf("%s: got: %p, expected: %p\n",
			RED"DIFF"RESET, got, expected);
		return (1);
	}
	return (0);
}

int		run_test(char *label, int fw, int (*test)())
{
	int	ret;

	ft_printf("%s %*s %s\n",
		BULLET, fw, label, (ret = (*test)()) ? PASS : FAIL);
	return (ret);
}
