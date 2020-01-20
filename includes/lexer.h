/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:57:54 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:27:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <token.h>

# define META			"\"\'\\()"

# define D_QUOTES		1
# define S_QUOTES		2
# define B_SLASH		4
# define PARENTH_IN		8
# define PARENTH_OUT	16

# define WAITING		15

char	*line_read(char *line);
t_token	*line_tokenize(char *line);
int		var_expand(t_token *token, void *env);

#endif
