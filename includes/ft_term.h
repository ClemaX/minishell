#ifndef FT_TERM_H
# define FT_TERM_H

# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <term.h>
#include "fcntl.h"
#include "sys/stat.h"

# define MAX_ENTRY		1024
# define BASH_ERROR_CODE 127

# define TERM_PS1		"minish> "

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
# define TERM_SUSPEND	0b0000010000000000
# define TERM_CLEAR		0b0000100000000000
# define TERM_SELECT	0b0001000000000000
# define TERM_IGNORE	0b0010000000000000

# define TERM_WAITING	(TERM_B_SLASH | TERM_S_QUOTE | TERM_D_QUOTE)
# define TERM_CONSUME	(TERM_NEWLINE | TERM_CLEAR | TERM_INT | TERM_EOF | TERM_STOP | TERM_ERASE | TERM_SUSPEND | TERM_IGNORE)

# define TAKE_FD		1
# define GIVE_FD		2

typedef struct	s_line
{
	char			*data;
	size_t			length;
	size_t			size;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

typedef struct	s_caps
{
	char	*insert;
	char	*insert_end;
	char	*clear;
	char	*standout;
	char	*standout_end;
	char	*k_up;
	char	*k_down;
	char	*k_left;
	char	*k_right;
	char	*c_del;
	char	*c_del_n;
	char	*c_del_line;
	char	*c_move;
	char	*c_move_h;
	char	*c_up;
	char	*c_down;
	char	*c_left;
	char	*c_right;
}				t_caps;

typedef struct	s_position
{
	unsigned	x;
	unsigned	y;
}				t_position;

typedef struct	s_cursor
{
	t_position	pos;
	t_position	origin;
}				t_cursor;


typedef struct	s_selection
{
	t_position	start;
	t_position	end;
}				t_selection;


typedef struct	s_hist
{
	t_line	*last;
	t_line	*curr;
	t_line	*next;
	// TODO: Remove next
}				t_hist;

typedef struct  s_pipe
{
	int			fd[2];
	int			w;
	int			r;
	int			in;
	int			out;
}				t_pipe;

typedef	struct	s_term
{
	const char		*name;
	int				pid;
	struct termios	s_ios;
	struct termios	s_ios_bkp;
	t_cursor		cursor;
	t_selection		select;
	t_caps			caps;
	t_map			*env;
	t_line			*line;
	t_hist			hist;
	t_line			clip;
	int				(*exec)(const char*, struct s_term*);
	int				flags;
	int				fd[2];
	int				st;
}				t_term;

int				term_init(t_term *t, const char **envp, int (*exec)(const char*, t_term*));
int				term_destroy(t_term *t);
int				term_prompt(int ac, const char **av, const char **envp, int (*exec)(const char*, t_term*));
int				term_input(t_term *t, int status);
int				input_special(int status, char c);

void			term_up(t_term *t);
void			term_down(t_term *t);

void			term_left(t_term *t);
void			term_right(t_term *t);
void			term_start_line(t_term *t);
void			term_end_line(t_term *t);

int				term_prewrite(t_term *t, const char *str, size_t n);
int 			term_write(t_term *t, const char *str, size_t n);
void			term_clear_line(t_term *t);
void			term_clear_screen(t_term *t, int status);

void			term_write_prompt(t_term *t, int status);

int				term_cancel(t_term *t);
int				term_new_line(t_term *t, int status);
void			term_stop(t_term *t);
int				term_erase(t_term *t, int status);

void			hist_add(t_hist *hist, t_line *line);
void			hist_clear(t_hist *hist);
void			hist_pop(t_hist *hist);
void			hist_commit(t_hist *hist, t_line *line);

t_line			*line_dup(t_line *line);
t_line			*line_new(size_t size);

int				line_insert_at(t_line *line, size_t at, const char *str, size_t n);
int				line_erase_at(t_line *line, size_t at, size_t n);
void			line_clear(t_line **line);

void			selection_left(t_term *t);
void			selection_right(t_term *t);
void			selection_clear(t_term *t);

char			*clip_copy(t_term *t);
char			*clip_cut(t_term *t);
int				clip_paste(t_term *t);
void			clip_clear(t_line *clip);

#endif
