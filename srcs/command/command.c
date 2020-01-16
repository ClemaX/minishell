/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 20:33:01 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <command.h>
#include <libft.h>
#include <line.h>
#include <stdlib.h>
#include <unistd.h>

t_status		cmd_parse(t_cmd *cmd, char **line, t_status status)
{
	static t_line	*arg;
	static t_line	*args;

	if (!(status & (QUOTE | B_SLASH)))
		args_clr(&args, cmd);
	status &= ~B_SLASH;
	while (**line && !(status & SEMICOL))
	{
		while (ft_isspace(**line))
			(*line)++;
		status = arg_parse(cmd, &arg, line, status);
		if (arg && !status)
			arg_add(&args, &arg, cmd);
	}
	status &= ~SEMICOL;
	if (!(status & (QUOTE | B_SLASH)))
		args_export(cmd, args);
	return (status);
}
