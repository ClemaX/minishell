/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 21:18:30 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 04:42:49 by chamada     ###    #+. /#+    ###.fr     */
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
	OP_AND,
	OP_PIPE,
	OP_LESSER,
	OP_GREATER,
	OP_OR,
	TOKEN
}				t_token_t;

int		token_foreach(t_token *tokens, void *param, int (f)(t_token*, void*));
t_token	*token_add(t_token **tokens, char *data, t_token_t type);

#endif
