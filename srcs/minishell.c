/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:38:55 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/12 04:45:56 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <command.h>

int	main(int ac, char **av)
{
	t_cmd	command;
	char	*line;
	int		fd;

	if (ac == 1)
		fd = 0;
	else if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		return (1);
	while (get_next_line(fd, &line) > 0)
	{
		parse_cmd(&command, line);
		free(line);
	}
	return (0);
}