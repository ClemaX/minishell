/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/12 04:43:38 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 04:38:51 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <map.h>
# include <token.h>
# include <line.h>

typedef int			t_status;

typedef struct		s_cmd
{
	int		ac;
	char	**av;
	t_map	*env;
	int		op;
	int		ret;
}					t_cmd;

int					args_export(t_cmd *cmd, t_token *args);
void				args_print(t_line *args);
void				arg_add(t_token **args, t_token **arg, t_cmd *cmd);
void				args_clr(t_token **args, t_cmd *cmd);
int					cmd_exec(t_cmd *cmd, char *name, int (x)(char *,
	t_cmd *));
int					key_check(char *key);
#endif
