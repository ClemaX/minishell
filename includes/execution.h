/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execution.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:40:28 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/24 18:24:45 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <command.h>
#include <map.h>
#include <parser.h>

typedef struct s_pipe
{
	char	in;
	char	out;
	int		fd_read;
	int		fd_write;
	int		pipe_fd[2];
	int		stdout;
}				t_pipe;

int		simple_cmd(t_node *node, t_map *env, char *name, int (exec)(char *,
	t_cmd *));
void	cmd_line_execution(t_node *node, t_map *env, char *name);
int		redirection(t_node *node, char std, t_map *env, char *name);
int		ft_pipe(t_node *node, t_map *env, char *name);
int		ft_execve_f(char *exec, t_cmd *cmd);
int		ft_execve(char *exec, t_cmd *cmd);

#endif