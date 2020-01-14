/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:43:38 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 08:50:04 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include <map.h>

# define S_CHAR	"\"\'\\"

# define D_QUOTE		1
# define S_QUOTE		2
# define BACKSLASH		4

typedef char	t_status;

typedef struct	s_cmd
{
	int		ac;
	char	**av;
	t_map	*env;
	int		op;
}				t_cmd;

t_status		parse_cmd(t_status status, t_cmd *cmd, char *line);

#endif
