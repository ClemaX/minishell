/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 13:47:32 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <command.h>
#include <unistd.h>

static	int	print_status(t_status status, t_cmd *cmd)
{
	if (status)
		ft_printf("> ");
	else
		ft_printf("%s>$ ", map_get(cmd->env, "PWD")->value);
	return (1);
}

int			main(int ac, char **av, const char **envp)
{
	t_cmd			cmd;
	t_status		status;
	char			*line;
	int				fd;

	line = NULL;
	cmd.ac = 0;
	cmd.av = NULL;
	cmd.env = map_load(envp);
	status = 0;
	cmd.ret = 0;
	if (ac == 1)
		fd = 0;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (1);
	while (print_status(status, &cmd) && get_next_line(fd, &line) > 0)
	{
		status = cmd_parse(&cmd, line, status);
		cmd.ret = minish(&cmd, av);
		free(line);
	}
	free(line);
	free(cmd.av);
	ft_printf("exit\n");
	return (cmd.ret);
}
