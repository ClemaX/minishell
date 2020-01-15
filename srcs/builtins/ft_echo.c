/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:44:06 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 12:03:41 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>

int	ft_echo(int ac, char **argv, char **envp)
{
	char	opt;
	short	arg;
	char	**env;

	env = envp;
	arg = 1;
	opt = 0;
	if (ac > 1)
	{
		if ((opt = (ft_strncmp("-n", argv[1], 3) == 0)))
		{
			ac--;
			arg++;
		}
		while (--ac)
			ac != 1 ? ft_printf("%s ", argv[arg++])
			: ft_printf("%s", argv[arg++]);
	}
	!opt ? ft_printf("\n") : 0;
	return (0);
}
