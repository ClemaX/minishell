/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minish_cmd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 08:51:26 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 09:49:08 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "command.h"
#include "builtins.h"

int		minish(t_cmd *cmd, char **av, int ret)
{
	if (!ft_strncmp(cmd->av[0], "echo", 5))
		return (ft_echo(cmd->ac, cmd->av, cmd->env));
	if (!ft_strncmp(cmd->av[0], "cd", 3))
		return (ft_cd(cmd->ac, cmd->av, cmd->env));
	if (!ft_strncmp(cmd->av[0], "pwd", 4))
		return (ft_cd());
	if (!ft_strncmp(cmd->av[0], "export", 7))
		return (ft_cd(cmd->ac, cmd->av, cmd->env));
	if (!ft_strncmp(cmd->av[0], "unset", 6))
		return (ft_cd(cmd->ac, cmd->av, cmd->env));
	if (!ft_strncmp(cmd->av[0], "env", 4))
		return (ft_cd(cmd->ac, cmd->av, cmd->env));
	if (!ft_strncmp(cmd->av[0], "exit", 5))
		return (ft_cd());
	if (!ft_strncmp(cmd->av[0], "$?", 3))
		ft_printf("%i", ret);
	else
	{
		ft_printf("%s: %s: command not found", av[0], cmd->av[0]);
		ret = 127;
	}
}
