/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   builtins.h                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:11:33 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 11:16:48 by plamtenz    ###    #+. /#+    ###.fr     */
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

/*
**-------------------------------- PROTOTYPES ----------------------------------
*/
int     ft_echo(int ac, char **argv, char **envp);
int     ft_pwd(void);
int     ft_exit(void);
int		ft_cd(int ac, char **argv, char **envp);
int		ft_env(int ac, char **argv, char **envp);
int		ft_unset(int ac, char **argv, char **envp);

#endif
