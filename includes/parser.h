/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 21:17:36 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 01:43:37 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <token.h>

typedef enum	e_node_t
{
	NODE_SEQ = OP_SEMICOLON,
	NODE_BG = OP_AMPERSAND,
	NODE_PIPE = OP_PIPE,
	NODE_R_IN = OP_LESSER,
	NODE_R_OUT = OP_GREATER,
	NODE_ARG,
	NODE_CMD
}				t_node_t;

typedef struct	s_node
{
	t_node_t		type;
	char			*data;
	struct s_node	*ch1;
	struct s_node	*ch2;
}				t_node;

char			check_type(t_token **token, t_type type, char **buffer);
t_node			*arg_list(t_token **token);
t_node			*command(t_token **token);
t_node			*job(t_token **token);
t_node			*cmd_line(t_token **token);
int				parse(t_token *tokens);
void			node_del(t_node *node);

#endif
