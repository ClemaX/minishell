#include <ft_term.h>

static int	handle_escape(int status)
{
	int		ret;
	char	c[2];

	ret = read(0, c, 2);
	if (ret == 0)
		return (status & ~TERM_READING);
	if (ret == -1)
		return ((status | TERM_ERROR) & ~TERM_READING);
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
	if (c == g_term.s_ios.c_cc[VERASE])
		return (status | TERM_ERASE);
	if (c == g_term.s_ios.c_cc[VEOF])
		return (status | TERM_EOF);
	if (c == g_term.s_ios.c_cc[VSTOP])
		return (status | TERM_STOP);
	return (status);
}

static int	handle_special(int status, char c)
{
	if (c == '\n')
		status |= TERM_NEWLINE;
	else if (status & TERM_B_SLASH)
		return (status & ~TERM_B_SLASH);
	else if (c == '"')
		status ^= TERM_D_QUOTE;
	else if (!(status & TERM_D_QUOTE) && c == '\'')
		status ^= TERM_S_QUOTE;
	else if (!(status & TERM_B_SLASH) && c == '\\')
		status |= TERM_B_SLASH;
	return (status);
}

static int	handle_status(int status)
{
	if (status & TERM_INT)
		status = term_cancel();
	if (status & TERM_NEWLINE)
		term_new_line(status);
	if (status & TERM_EOF && g_term.hist->length == 0)
		status &= ~TERM_READING;
	if (status & TERM_STOP)
		term_stop();
	if (status & TERM_ERASE)
		term_erase();
	return (status & ~TERM_CONSUME);
}

int         term_input(int status)
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
	status = handle_control(status, c);
	if ((status & (TERM_READING | TERM_CONSUME)) == TERM_READING)
	{
		status = handle_special(status, c);
		write(1, &c, 1);
		if (line_append(g_term.hist, c) == -1)
			return ((status | TERM_ERROR) & ~TERM_READING);
	}
	status = handle_status(status);
	return (status);
}
