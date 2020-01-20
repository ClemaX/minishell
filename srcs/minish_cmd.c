/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minish_cmd.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 08:51:26 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 09:56:01 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "command.h"
#include "builtins.h"
#include <map.h>
#include <env.h>
#include <unistd.h>
#include <errno.h>
#include <libft.h>

int		cmd_exec(t_cmd *cmd, char *name)
{
	char	*exec;

	if (!cmd->ac)
		return (0);
	if (!ft_strncmp(cmd->av[0], "echo", 5))
		return (ft_echo(cmd->ac, cmd->av, map_export(cmd->env)));
	if (!ft_strncmp(cmd->av[0], "cd", 3))
		return (ft_cd(cmd->ac, cmd->av, cmd));
	if (!ft_strncmp(cmd->av[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(cmd->av[0], "export", 7))
		return (ft_export(cmd->ac, cmd->av, cmd, name));
	if (!ft_strncmp(cmd->av[0], "unset", 6))
		return (ft_unset(cmd, name));
	if (!ft_strncmp(cmd->av[0], "env", 4))
		return (ft_env(cmd->glob_env));
	if (!ft_strncmp(cmd->av[0], "exit", 5))
		return (ft_exit());
	else if ((exec = path_get(cmd->env, cmd->av[0])))
	{
		execve(exec, cmd->av, map_export(cmd->env));
		ft_printf("execve returned! errno is [%d]\n", errno);
		return (0);
	}
	else
	{
		ft_printf("%s: %s: command not found\n", name, cmd->av[0]);
		return (127);
	}
}
