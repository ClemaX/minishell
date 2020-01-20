/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:49:04 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 09:28:25 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

int		map_test(int ac, const char **av, const char **ep);
int		path_test(const char **ep);
char	*lexer_test(const char *name, const char **ep);
int		prompt_test(void);

#endif