#ifndef LEXER_H
# define LEXER_H

# include <libft.h>
# include <stdlib.h>
# include <stdbool.h>

# define LEX_TOKEN		0b00001
# define LEX_B_SLASH	0b00010
# define LEX_S_QUOTE	0b00100
# define LEX_D_QUOTE	0b01000
# define LEX_OP			0b10000

# define OPERATORS		";&|><()"

# define TOK_TOKEN		0b0001
# define TOK_OP			0b0010

typedef short	t_token_t;


typedef struct	s_par
{
	int				level;
	int				fd;
	bool			cond;
}				t_par;

typedef struct  s_token // delete if char **
{
	char			*data;
	t_token_t		type;
	struct s_token	*next;
	t_par			p;
}				t_token;

int				lexer_tokenize(const char *input, t_token **tokens,
	t_token **operators);

t_token			*parse_token(const char **txt);

t_token			*token_new(char *data, t_token_t type);
t_token			*token_add(t_token **tokens, t_token *new);
t_token			*token_clear(t_token **tokens);

t_token			*token_next_cmd(t_token **tokens);
const char		**token_tab(t_token *tokens, int *n);

#endif
