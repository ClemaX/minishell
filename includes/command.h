/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:43:38 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 10:31:39 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <line.h>
# include <map.h>

# define META		"\\\'\"$()"

# define B_SLASH	1
# define S_QUOTE	2
# define D_QUOTE	4
# define DOLLAR		8
# define PARENTH	16

# define QUOTE		6

typedef char		t_status;

typedef struct		s_cmd
{
	int		ac;
	char	**av;
	t_map	*env;
	int		op;
}					t_cmd;

t_status			cmd_parse(t_cmd *cmd, char *line, t_status status);
t_status			arg_parse(t_line **arg, char **line, t_status status);
int					args_export(t_cmd *cmd, t_line *args);
void				args_print(t_line *args);
int					minish(t_cmd *cmd, char **av, int ret);

#endif
