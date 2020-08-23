/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 06:49:04 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 16:10:45 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <sys/types.h>
# include <sys/wait.h>
# include <ft_term.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <diff.h>
# include <units.h>

# define LBL_FW -18
# define RESET	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define CYAN	"\033[0;36m"
# define TITLE	"\033[1;34m"
# define BULLET	CYAN"▶"RESET
# define PASS	GREEN"✔"RESET
# define FAIL	RED"✗"RESET

# define C_NONE	RED"C"RESET
# define C_MISC	RED"C"RESET
# define C_SEGV	RED"S"RESET
# define C_ABRT	RED"A"RESET

# define BASE_PLUS	"01234+"
# define BASE_MINUS	"01234-"
# define BASE_HEX	"0123456789ABCDEF"

int				run_tests(int *fd, char *label,
	int (*tests[])(), int iterations);

unsigned		ft_rand(unsigned min, unsigned max);
char			*rand_key(unsigned len);
char			*rand_val(unsigned len);
char			**rand_tab_map(int count, int len);

t_list			*lst_add_front(t_list **list, void *data);
void			lst_clear(t_list **list);

t_term			*rand_term(unsigned line_length);
void			rand_term_destroy(t_term *t);

#endif
