/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:43:38 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/13 07:29:40 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define S_CHAR	"\"\'\\"

# define D_QUOTE		1
# define S_QUOTE		2
# define BACKSLASH		4

typedef char	t_status;

typedef struct	s_cmd
{
	char	**av;
	int		ac;
	int		op;
}				t_cmd;

t_status		parse_cmd(t_status status, t_cmd *cmd, char *line);

#endif