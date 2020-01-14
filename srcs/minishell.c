/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 10:12:50 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>
#include <command.h>
#include <unistd.h>

int			main(int ac, char **av, char **envp)
{
	t_cmd		command;
	int			ret;
	t_status	status;
	char		*line;
	int			fd;

	(void)envp;
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
		status = parse_cmd(status, &command, line);
		free(line);
		ret = minish(&command, av, ret);
	}
	return (0);
}
