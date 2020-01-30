/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 22:57:54 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/30 04:33:55 by chamada     ###    #+. /#+    ###.fr     */
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

char	*line_parse(char *str);
t_token	*line_tokenize(char *line);
int		var_expand(t_token *token, void *env);
int		var_assign(t_token *token, void *env);
int	    tilde_expand(t_token *token, void *env);
int		set_token_type_op(t_token *token, void *param);

#endif
