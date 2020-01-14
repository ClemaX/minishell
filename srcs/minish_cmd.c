/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minish_cmd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 08:51:26 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 11:56:34 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "command.h"
#include "builtins.h"
#include <map.h>

int		minish(t_cmd *cmd, char **av, int ret)
{
	if (!ft_strncmp(cmd->av[0], "echo", 5))
		return (ft_echo(cmd->ac, cmd->av, map_export(cmd->env)));
	if (!ft_strncmp(cmd->av[0], "cd", 3))
		return (ft_cd(cmd->ac, cmd->av, map_export(cmd->env)));
	if (!ft_strncmp(cmd->av[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->av[0], "export", 7))
	{
		//return (ft_export(cmd->ac, cmd->av, cmd->env));
		return (1);
	}
	if (!ft_strncmp(cmd->av[0], "unset", 6))
		return (ft_unset(cmd->ac, cmd->av, map_export(cmd->env)));
	if (!ft_strncmp(cmd->av[0], "env", 4))
		return (ft_env(cmd->ac, cmd->av, map_export(cmd->env)));
	if (!ft_strncmp(cmd->av[0], "exit", 5))
		return (ft_exit());
	if (!ft_strncmp(cmd->av[0], "$?", 3))
		ft_printf("%i", ret);
	else
	{
		ft_printf("%s: %s: command not found", av[0], cmd->av[0]);
		ret = 127;
	}
	return (ret);
}
