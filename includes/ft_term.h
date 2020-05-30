#ifndef FT_TERM_H
# define FT_TERM_H

# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <term.h>

# define TERM_READING	0b00000001
# define TERM_ERROR		0b00000010
# define TERM_B_SLASH	0b00000100
# define TERM_S_QUOTE	0b00001000
# define TERM_D_QUOTE	0b00010000
# define TERM_NEWLINE	0b00100000

# define TERM_WAITING	((TERM_B_SLASH | TERM_S_QUOTE) | TERM_D_QUOTE)

typedef struct	s_line
{
	char			*data;
	ssize_t			length;
	ssize_t			size;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef	struct	s_term
{
	int				pid;
	struct termios	s_ios;
	struct termios	s_ios_bkp;
	t_map			*env;
	t_line			*hist;
}				t_term;

extern t_term	g_term;

int				term_init(const char **envp);
int				term_prompt(void);
t_line			*history_add(t_line *prev);
void			history_clear(t_line **hist);
int				line_append(t_line *line, char c);
void			line_clear(t_line **line);

#endif
