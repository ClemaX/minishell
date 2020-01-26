/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   env.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 22:01:51 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:24:14 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <map.h>

char		*path_get(t_map *env, const char *exec);
char		**path_export(t_map *env);
char		*path_cat(const char *a, const char *b);

#endif
