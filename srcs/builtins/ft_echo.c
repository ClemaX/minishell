/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_echo.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:44:06 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 05:32:32 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <command.h>

int	ft_echo(t_cmd *cmd)
{
	char	opt;
	int		i;

	opt = 0;
	i = 1;
	if (cmd->ac > 1)
	{
		if ((opt = (ft_strncmp("-n", cmd->av[1], 3) == 0)))
			i++;
		while (i < cmd->ac)
		{
			ft_printf((i != cmd->ac - 1) ? "%s " : "%s", cmd->av[i]);
			i++;
		}
	}
	if (!opt)
		ft_printf("\n");
	return (0);
}
