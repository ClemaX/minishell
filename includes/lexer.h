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

#define OPEN_PAR        1
#define CLOSE_PAR       2
#define T_AND           4
#define T_OR            8
#define T_PIPE          16
#define T_DGRAT         32
#define T_DLESS         64
#define T_GRAT          128
#define T_LESS          256
#define T_SEM           512

typedef short	t_token_t;

typedef struct  s_token
{
	char			*data;
	t_token_t		type;
	struct s_token	*next;
}				t_token;

t_token			*lexer_tokenize(const char *input);

t_token			*parse_token(const char **txt);

#endif
