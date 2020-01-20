/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:21:13 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <command.h>
#include <libft.h>
#include <line.h>
#include <stdlib.h>
#include <unistd.h>
#include <parser.h>

t_status		cmd_parse(t_cmd *cmd, char **line, t_status status)
{
	static t_token	*arg;
	static t_token	*args;

	if (!(status & (QUOTE | SLASH)))
		args_clr(&args, cmd);
	status &= ~SLASH;
	while (**line)
	{
		while (ft_isspace(**line))
			(*line)++;
		status = arg_parse(cmd, &arg, line, status);
		if (arg && !status)
			arg_add(&args, &arg, cmd);
	}
	parse(args);
	if (!(status & (QUOTE | SLASH)))
		args_export(cmd, args);
	return (status);
}
