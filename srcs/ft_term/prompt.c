#include <ft_term.h>

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

static int	read_char(int status)
{
	int		ret;
	char	c;

	ret = read(0, &c, 1);
	if (ret == 0)
		status &= ~TERM_READING;
	else if (ret == -1)
	{
		status &= ~TERM_READING;
		status |= TERM_ERROR;
	}
	else {
		status = handle_special(status, c);
		if (line_append(g_term.hist, c) == -1)
		{
			status &= ~TERM_READING;
			status |= TERM_ERROR;
		}
	}
	return (status);
}

static int	handle_status(int status)
{
	if (status & TERM_NEWLINE)
	{
		status &= ~TERM_NEWLINE;
		g_term.hist = history_add(g_term.hist);
		if (status & TERM_WAITING)
			ft_printf("> ");
		else
			ft_printf("minish> ");
		status &= ~TERM_B_SLASH;
	}
	return (status);
}

int		term_prompt(void)
{
	int		status;

	if (!(g_term.hist = history_add(NULL)))
		return (-1);
	status = TERM_READING;
	ft_printf("minish> ");
    while ((status = read_char(status)) & TERM_READING)
	{
		status = handle_status(status);
	}
	if (term_destroy() == -1)
        status |= TERM_ERROR;
	return ((status & TERM_ERROR) ? -1 : 0);
}
