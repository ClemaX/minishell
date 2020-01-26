/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tests.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:49:04 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 21:14:45 by chamada     ###    #+. /#+    ###.fr     */
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

int		diff_s(char *got, char *expected);
int		diff_p(void *got, void *expected);
int		run_test(char *label, int fw, int (*test)());

char	*rand_key(int len);
char	*rand_val(int len);
char	**rand_tab_map(int count, int len);

int		tab_print(char **tab);
void	*tab_unload(char **tab);
int		tab_cmp(char **tab, char **expected);

int		map_test();
int		line_test();
int		path_test();
int		lexer_test();
int		prompt_test();

void	error(void);

#endif
