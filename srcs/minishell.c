/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 11:01:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <command.h>
#include <unistd.h>

static int	print_tab(char **tab)
{
	if (!tab)
		return (0);
	while (*tab)
		ft_printf("%s\n", *tab++);
	return (0);
}

int			main(int ac, char **av, const char **envp)
{
	t_cmd			command;
	int				ret;
	t_status		status;
	char			*line;
	int				fd;

	line = NULL;
	command.ac = 0;
	command.av = NULL;
	command.env = map_load(envp);
	status = 0;
	ret = 0;
	if (ac == 1)
		fd = 0;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (1);
	while (ft_printf(status ? "> " : "minish-1.0$ ")
	&& get_next_line(fd, &line) > 0)
	{
		status = cmd_parse(&command, line, status);
		print_tab(command.av);
		free(line);
	}
	free(line);
	free(command.av);
	return (0);
}
