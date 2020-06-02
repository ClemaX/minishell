#ifndef FT_TERM_H
# define FT_TERM_H

# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <term.h>

# define MAX_ENTRY		1024

# define TERM_READING	0b0000000000000001
# define TERM_ERROR		0b0000000000000010
# define TERM_B_SLASH	0b0000000000000100
# define TERM_S_QUOTE	0b0000000000001000
# define TERM_D_QUOTE	0b0000000000010000
# define TERM_NEWLINE	0b0000000000100000
# define TERM_INT		0b0000000001000000
# define TERM_ERASE		0b0000000010000000
# define TERM_EOF		0b0000000100000000
# define TERM_STOP		0b0000001000000000

# define TERM_WAITING	(TERM_B_SLASH | TERM_S_QUOTE | TERM_D_QUOTE)
# define TERM_CONSUME	(TERM_NEWLINE | TERM_INT | TERM_EOF | TERM_STOP | TERM_ERASE)

typedef struct	s_line
{
	char			*data;
	ssize_t			length;
	ssize_t			size;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef struct	s_caps
{
	char	*k_up;
	char	*k_down;
	char	*k_left;
	char	*k_right;
	char	*c_del;
	char	*c_up;
	char	*c_down;
	char	*c_left;
	char	*c_right;
}				t_caps;

typedef struct	s_cursor
{
	unsigned	x;
	unsigned	y;
}				t_cursor;


typedef	struct	s_term
{
	int				pid;
	struct termios	s_ios;
	struct termios	s_ios_bkp;
	t_caps			caps;
	t_map			*env;
	t_line			*hist;
}				t_term;

extern t_term	g_term;

int				term_init(const char **envp);
int				term_destroy(void);
int				term_prompt(void);
int				term_input(int status);

void			term_up(void);
void			term_down(void);
void			term_left(void);
void			term_right(void);

int				term_cancel(void);
void			term_new_line(int status);
void    		term_stop(void);
void    		term_erase(void);

t_line			*history_add(t_line *prev);
void			history_clear(t_line **hist);
int				line_append(t_line *line, char c);
void			line_clear(t_line **line);

#endif
