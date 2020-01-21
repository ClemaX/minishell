/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execution.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:40:28 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/21 11:26:41 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <command.h>
#include <map.h>
#include <parser.h>

void	simple_cmd(t_node *node, t_map *env, char *name, int (exec)(char *,
	t_cmd *));
void	cmd_line_execution(t_node *node, t_map *env, char *name);
void	redirection(t_node *node, char *data, char std, t_map *env, char *name);
void	ft_pipe(t_node *node, t_map *env, char *name);
int		ft_execve_f(char *exec, t_cmd *cmd);
int		ft_execve(char *exec, t_cmd *cmd);

#endif