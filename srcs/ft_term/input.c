#include <ft_term.h>

static int	handle_alt_escape(int status)
{
	char	c[3];

	read(0, c, 3);
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
	if (c[1] == '1')
		return (handle_alt_escape(status));
	else if (status & TERM_SELECT)
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
	if (c == g_term.s_ios.c_cc[VERASE])
		return (status | TERM_ERASE);
	if (c == g_term.s_ios.c_cc[VEOF])
		return (status | TERM_EOF);
	if (c == g_term.s_ios.c_cc[VSTOP])
		return (status | TERM_STOP);
	if (c == '\014')
		return (status | TERM_CLEAR);
	return (status);
}

static int	handle_special(int status, char c)
{
	if (status & TERM_B_SLASH)
		return (status & ~TERM_B_SLASH);
    if (!(status & TERM_WAITING) && c == '\n')
		status |= TERM_NEWLINE;
	else if (!(status & TERM_S_QUOTE) && c == '"')
		status ^= TERM_D_QUOTE;
	else if (!(status & TERM_D_QUOTE) && c == '\'')
		status ^= TERM_S_QUOTE;
	else if (!(status & TERM_B_SLASH) && c == '\\')
		status |= TERM_B_SLASH;
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
	status = handle_control(status, c);
	if ((status & (TERM_READING | TERM_CONSUME)) == TERM_READING)
	{
		status = handle_special(status, c);
		if (!(status & TERM_CONSUME) && !term_write(&c, 1))
			return ((status | TERM_ERROR) & ~TERM_READING);
	}
	return (status);
}
