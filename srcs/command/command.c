/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 15:43:31 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

/*
** TO DO : ESCAPABLE CHARS FCT
*/

#include <command.h>
#include <libft.h>
#include <line.h>
#include <stdlib.h>
#include <unistd.h>

t_status		cmd_parse(t_cmd *cmd, char *line, t_status status)
{
	static t_line	*arg = NULL;
	static t_line	*args = NULL;

	status &= ~B_SLASH;
	if (!(status & QUOTE))
	{
		line_clr(&args);
		free(cmd->av);
		cmd->ac = 0;
		cmd->av = NULL;
	}
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		status = arg_parse(cmd, &arg, &line, status);
		if (arg && !status)
		{
			arg->next = args;
			args = arg;
			arg = NULL;
			cmd->ac++;
		}
	}
	args_export(cmd, args);
	return (status);
}
