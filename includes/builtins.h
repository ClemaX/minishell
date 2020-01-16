/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 06:11:33 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/16 22:04:01 by plamtenz         ###   ########.fr       */
/*                                                                            */
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
int                     ft_echo(int ac, char **argv, char **envp);
int                     ft_pwd(void);
int                     ft_exit(void);
int                     ft_cd(int ac, char **argv, t_cmd *cmd);
int                     ft_env(t_map *env);
int                     ft_unset(t_cmd *cmd, char *name);
int                     ft_export(int ac, char **av, t_cmd *cmd, char *name);

#endif
