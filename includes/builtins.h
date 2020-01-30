/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:11:33 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 05:23:14 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#ifndef BUILTINGS_H
# define BUILTINGS_H

/*
**---------------------------- MACROS BITWISE ---------------------------------
*/
# define BT_ECHO        2
# define BT_CD          4
# define BT_PWD         8
# define BT_EXPORT      16
# define BT_UNSET       32
# define BT_ENV         64
# define BT_EXIT        128

/*
**--------------------------------- INCLUDES -----------------------------------
*/
#include <libft.h>
#include <limits.h>
#include <map.h>

/*
**-------------------------------- PROTOTYPES ----------------------------------
*/
int                     ft_echo(t_cmd *cmd);
int                     ft_pwd(void);
int                     ft_exit(void);
int                     ft_cd(t_cmd *cmd);
int                     ft_env(t_map *env);
int                     ft_unset(t_cmd *cmd, char *name);
int                     ft_export(t_cmd *cmd, char *name);

#endif
