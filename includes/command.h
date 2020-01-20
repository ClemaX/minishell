/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:43:38 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:20:42 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <token.h>
# include <line.h>
# include <map.h>


# define META		"\\\'\"$=()"

# define SLASH		1
# define S_QUOTE	2
# define D_QUOTE	4
# define QUOTE		6

# define DOLLAR		8
# define EQUAL		16
# define PARENTH	32


typedef int			t_status;

typedef struct		s_cmd
{
	int		ac;
	char	**av;
	t_map	*env;
	t_map	*glob_env;
	int		op;
	int		ret;
}					t_cmd;

t_status			cmd_parse(t_cmd *cmd, char **line, t_status status);
t_status			arg_parse(t_cmd *cmd, t_token **arg, char **line,
	t_status status);
t_status			status_handler(t_cmd *cmd, t_line **arg, char **line,
	t_status status);
int					args_export(t_cmd *cmd, t_token *args);
void				args_print(t_line *args);
void				arg_add(t_token **args, t_token **arg, t_cmd *cmd);
void				args_clr(t_token **args, t_cmd *cmd);
int					key_check(char *key);
int					minish(t_cmd *cmd, char **av);

#endif
