/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 21:18:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 02:18:07 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef unsigned int	t_type;

typedef struct	s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}				t_token;

typedef enum	e_token_t
{
	OP_SEMICOLON,
	OP_AMPERSAND,
	OP_PIPE,
	OP_LESSER,
	OP_GREATER,
	TOKEN
}				t_token_t;

int	token_foreach(t_token *tokens, void *param, int (f)(t_token*, void*));

#endif
