#include <ft_term.h>

static int	handle_alt_escape(int status)
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
		if (c[2] == g_term.caps.k_left[2]) // LEFT
			selection_left();
		else if (c[2] == g_term.caps.k_right[2]) // RIGHT
			selection_right();
		return(status | TERM_SELECT);
	}
	else if (c[1] == '5') // CONTROL
		ft_dprintf(2, "[PROMPT] ctrl + %c\n", c[2]);
	return (status);
}

static int	handle_escape(int status)
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
		return (handle_alt_escape(status));
	if (status & TERM_SELECT)
	{
		status &= ~TERM_SELECT;
		selection_clear();
	}
	if (c[1] == g_term.caps.k_up[2])
		term_up();
	else if (c[1] == g_term.caps.k_down[2])
		term_down();
	else if (c[1] == g_term.caps.k_left[2])
		term_left();
	else if (c[1] == g_term.caps.k_right[2])
		term_right();
	return (status);
}

static int	handle_control(int status, char c)
{
	if (c == g_term.s_ios.c_cc[VINTR])
		return (status | TERM_INT);
	if (c == g_term.s_ios.c_cc[VERASE] || c == 'h' - 'a' + 1)
		return (status | TERM_ERASE);
	if (c == g_term.s_ios.c_cc[VEOF])
		return (status | TERM_EOF);
	if (c == g_term.s_ios.c_cc[VSTOP])
		return (status | TERM_STOP);
	if (c == g_term.s_ios.c_cc[VSUSP])
		return (status | TERM_SUSPEND);
	if (c == 'l' - 'a' + 1)
		return (status | TERM_CLEAR);
	if (c == '\n')
		return (status | TERM_NEWLINE);
	if (c == 'a' - 'a' + 1)
		term_start_line();
	else if (c == 'e' - 'a' + 1)
		term_end_line();
	else if (c == 'y' - 'a' + 1)
		clip_paste();
	else if (c == 'k' - 'a' + 1)
		clip_cut();
	else if (c == 'p' - 'a' + 1)
		term_up();
	else if (c == 'n' - 'a' + 1)
		term_down();
	if (c <= 26 && c != '\n')
	{
		ft_dprintf(2, "[PROMPT] ctrl + %c (%d)\n", c + 'a' - 1, c);
		return (status | TERM_IGNORE);
	}
	return (status);
}

int			term_input(int status)
{
	int		ret;
	char	c;

	ret = read(0, &c, 1);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (c == '\033')
		return (handle_escape(status));
	if (ft_iscntrl(c))
		return (handle_control(status, c));
	if (!term_write(&c, 1))
		return ((status | TERM_ERROR) & ~TERM_READING);
	return (status);
}
