/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 19:34:48 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <command.h>
#include <unistd.h>

static int	print_status(t_status status, t_cmd *cmd)
{
	if (status)
		ft_printf("> ");
	else
		ft_printf("%s>$ ", map_get(cmd->glob_env, "PWD")->value);
	return (1);
}


t_map		*map_dup(t_map	*map)
{
	t_map	*curr;
	t_map	*dup;

	dup = NULL;
	curr = map;
	while (curr)
	{
		map_set(&dup, curr->key, curr->value);
		curr = curr->next;
	}
	return (dup);
}

int			main(int ac, char **av, const char **envp)
{
	t_cmd			cmd;
	t_status		status;
	char			*line;
	char			*start;
	int				fd;

	line = NULL;
	cmd.ac = 0;
	cmd.av = NULL;
	cmd.glob_env = map_load(envp);
	status = 0;
	cmd.ret = 0;
	if (ac == 1)
		fd = 0;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (1);
	cmd.env = map_dup(cmd.glob_env);
	while (print_status(status, &cmd) && get_next_line(fd, &line) > 0)
	{
		start = line;
		while (*line)
		{
			status = cmd_parse(&cmd, &line, status);
			if (!(status & (QUOTE | B_SLASH)))
				cmd.ret = minish(&cmd, av);
		}
		free(start);
	}
	free(line);
	free(cmd.av);
	ft_printf("exit\n");
	return (cmd.ret);
}
