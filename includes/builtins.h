/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:11:33 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 18:27:23 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#ifndef BUILTINGS_H
# define BUILTINGS_H

/*
**--------------------------------- INCLUDES -----------------------------------
*/
#include <libft.h>
#include <limits.h>
#include <map.h>

/*
**-------------------------------- PROTOTYPES ----------------------------------
*/
int     ft_echo(int ac, char **argv, char **envp);
int     ft_pwd(void);
int     ft_exit(void);
int		ft_cd(int ac, char **argv, t_map **env);
int		ft_env(t_map *env);
int		ft_unset(t_cmd *cmd, char *name);
int		ft_export(int ac, char **av, t_cmd *cmd, char *name);

#endif
