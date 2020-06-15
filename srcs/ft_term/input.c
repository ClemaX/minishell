#include <ft_term.h>

static int	handle_alt_escape(t_term *t, int status)
{
	int		ret;
	char	c[3];

	ret = read(0, c, 3);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (ret != 3)
		return (status);
	if (c[1] == '2') // SHIFT
	{
		if (c[2] == t->caps.k_left[2]) // LEFT
			selection_left(t);
		else if (c[2] == t->caps.k_right[2]) // RIGHT
			selection_right(t);
		return(status | TERM_SELECT);
	}
	else if (c[1] == '5') // CONTROL
		ft_dprintf(2, "[PROMPT] ctrl + %c\n", c[2]);
	return (status);
}

static int	handle_escape(t_term *t, int status)
{
	int		ret;
	char	c[2];

	ret = read(0, c, 2);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (ret != 2)
		return (status);
	if (c[1] == '1')
		return (handle_alt_escape(t, status));
	if (status & TERM_SELECT)
	{
		status &= ~TERM_SELECT;
		selection_clear(t);
	}
	if (c[1] == t->caps.k_up[2])
		term_up(t);
	else if (c[1] == t->caps.k_down[2])
		term_down(t);
	else if (c[1] == t->caps.k_left[2])
		term_left(t);
	else if (c[1] == t->caps.k_right[2])
		term_right(t);
	return (status);
}

static int	handle_control(t_term *t, int status, char c)
{
	if (c == t->s_ios.c_cc[VINTR])
		return (status | TERM_INT);
	if (c == t->s_ios.c_cc[VERASE] || c == 'h' - 'a' + 1)
		return (status | TERM_ERASE);
	if (c == t->s_ios.c_cc[VEOF])
		return (status | TERM_EOF);
	if (c == t->s_ios.c_cc[VSTOP])
		return (status | TERM_STOP);
	if (c == t->s_ios.c_cc[VSUSP])
		return (status | TERM_SUSPEND);
	if (c == 'l' - 'a' + 1)
		return (status | TERM_CLEAR);
	if (c == '\n')
		return (status | TERM_NEWLINE);
	if (c == 'a' - 'a' + 1)
		term_start_line(t);
	else if (c == 'e' - 'a' + 1)
		term_end_line(t);
	else if (c == 'y' - 'a' + 1)
		clip_paste(t);
	else if (c == 'k' - 'a' + 1)
		clip_cut(t);
	else if (c == 'p' - 'a' + 1)
		term_up(t);
	else if (c == 'n' - 'a' + 1)
		term_down(t);
	if (c != '\n')
	{
		ft_dprintf(2, "[PROMPT] ctrl + %c (%d)\n", c + 'a' - 1, c);
		return (status | TERM_IGNORE);
	}
	return (status);
}

int			term_input(t_term *t, int status)
{
	int		ret;
	char	c;

	ret = read(0, &c, 1);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (c == '\033')
		return (handle_escape(t, status));
	if (ft_iscntrl(c))
		return (handle_control(t, status, c));
	selection_clear(t);
	if (!term_write(t, &c, 1))
		return ((status | TERM_ERROR) & ~TERM_READING);
	return (status);
}
