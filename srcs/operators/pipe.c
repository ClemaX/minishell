/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 20:06:30 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 23:11:17 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "unistd.h"
#include "stdio.h"
#include "builtins.h"

static int	pipe_engine(t_cmd *process, int *pipefd, int std)
{
	int pid;

	pid = fork();
	if ((pid < 0))
		return (-1);
	else if (!pid)
	{
		if (dup2(pipefd[0], std) < 0)
			return (-1);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

static int	made_in_42(char *built_in)
{
	int ret;

	ret = 0;
	ret = ret <= 0 && !ft_strmcmp("echo", built_in, 5) ? 2 : 0;
	ret = ret <= 0 && !ft_strmcmp("cd", built_in, 3) ? 4 : 0;
	ret = ret <= 0 && !ft_strmcmp("pwd", built_in, 4) ? 8 : 0;
	ret = ret <= 0 && !ft_strmcmp("export", built_in, 7) ? 16 : 0;
	ret = ret <= 0 && !ft_strmcmp("unset", built_in, 6) ? 32 : 0;
	ret = ret <= 0 && !ft_strmcmp("exit", built_in, 5) ? 128 : 0;
	return (ret > 0 ? 0 : 1);
}

static int	find_built_in(char *built_in, t_cmd *cmd, char **av)
{
	int	code;

	code = made_in_42(built_in);
	if (code & BT_ECHO)
		return (ft_echo(cmd->ac, cmd->av, map_export(cmd->env)));
	if (code & BT_CD)
		return (ft_cd(cmd->ac, cmd->av, cmd));
	if (code & BT_PWD)
		return (ft_pwd());
	if (code & BT_EXPORT)
		return (ft_export(cmd->ac, cmd->av, cmd, av[0]));
	if (code & BT_UNSET)
		return (ft_unset(cmd, av[0]));
	if (code & BT_ENV)
		return (ft_env(cmd->glob_env));
	if (code & BT_EXIT)
		return (ft_exit());
	return (-1);
}

int			ft_pipe(t_cmd *prcss1, t_cmd *prcss2, char **av)
{
	int	pipe_fd[2];

	if (!((unsigned long)prcss1 & (unsigned long)prcss2))
		return (-1);
	if (pipe(pipe_fd) < 0)
		return (-1);
	pipe_engine(prcss1, pipe_fd, STDIN_FILENO);
	made_in_42(prcss1->av[0])
		? execve(path_get(prcss1->glob_env, prcss1->av[0]),
		prcss1->av, map_export(prcss1->glob_env))
		: find_built_in(prcss1->av[0], prcss1, av);
	pipe_engine(prcss1, pipe_fd, STDOUT_FILENO);
	made_in_42(prcss2->av[0])
		? execve(path_get(prcss2->glob_env, prcss2->av[0]),
		prcss2->av, map_export(prcss2->glob_env))
		: find_built_in(prcss2->av[0], prcss2, av);
	while (wait(NULL) > 0)
		;
	return (0);
}
