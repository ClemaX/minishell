/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execution.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:40:28 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 09:17:50 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include <map.h>
#include <parser.h>

void	simple_cmd(t_node *node, t_map *env, char *name);
void	cmd_line_execution(t_node *node, t_map *env, char *name);
void	redirection(t_node *node, char *data, char std);
void	ft_pipe(t_node *node, t_map *env, char *name);

#endif