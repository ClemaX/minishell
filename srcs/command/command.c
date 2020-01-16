/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:45:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/16 19:35:40 by chamada     ###    #+. /#+    ###.fr     */
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

void			arg_add(t_line **args, t_line **arg, t_cmd *cmd)
{
	(*arg)->next = *args;
	*args = *arg;
	*arg = NULL;
	cmd->ac++;
}

t_status		cmd_parse(t_cmd *cmd, char **line, t_status status)
{
	static t_line	*arg;
	static t_line	*args;

	if (!(status & (QUOTE | B_SLASH)))
	{
		line_clr(&args);
		free(cmd->av);
		cmd->ac = 0;
		cmd->av = NULL;
	}
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
