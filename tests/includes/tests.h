/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:49:04 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 19:33:00 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# define RESET	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define CYAN	"\033[0;36m"
# define TITLE	"\033[1;34m"
# define PASS	GREEN"✔"RESET
# define FAIL	RED"✗"RESET
# define BULLET	CYAN"▶"RESET

int			diff_s(const char *got, const char *expected);
int			diff_p(const void *got, const void *expected);
int			run_test(const char *label, int fw, int (*test)());

const char	*rand_key(int len);
const char	*rand_val(int len);
const char	**rand_tab_map(int count, int len);

int			tab_print(const char **tab);
void		*tab_unload(char **tab);
int			tab_cmp(char **tab, const char **expected);


int			map_test(int ac, const char **av, const char **ep);
int			line_test(int ac, const char **av, const char **ep);
int			path_test(int ac, const char **av, const char **ep);
int			lexer_test(int ac, const char **av, const char **ep);
int			prompt_test(int ac, const char **av, const char **ep);

void		error(void);

#endif
