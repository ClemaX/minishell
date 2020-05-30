#include <ft_term.h>

t_term g_term = (t_term){.pid=0};

void	term_interrupt(int signal) {
	if (signal == SIGINT)
	{
		if (g_term.pid)
			kill(g_term.pid, SIGINT);
		write(0, "\n", 1);
	}
}

int		term_init(const char **envp)
{
	t_map		*term_type;

	signal(SIGINT, &term_interrupt);
	if (!(g_term.env = map_load(envp)))
		return (-1);
	if (!(term_type = map_get(g_term.env, "TERM"))
	|| tcgetattr(0, &g_term.s_ios) == -1)
		return (-1);
	g_term.s_ios_bkp = g_term.s_ios;
	return (0);
}

int		handle_special(int status, char c)
{
	if (c == '\n')
		status |= TERM_NEWLINE;
	else if (c == '"')
		status ^= TERM_D_QUOTE;
	else if (!(status & TERM_D_QUOTE) && c == '\'')
		status ^= TERM_S_QUOTE;
	else if (!(status & TERM_B_SLASH) && c == '\\')
		status &= TERM_B_SLASH;
	return (status);
}

int		read_char(int status)
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

int		handle_status(int status)
{
	if (status & TERM_NEWLINE)
	{
		status &= ~TERM_NEWLINE;
		g_term.hist = history_add(g_term.hist);
		if (status & TERM_WAITING)
			ft_printf("> ");
		else
			ft_printf("minish> ");
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
	history_clear(&g_term.hist);
	return ((status & TERM_ERROR) ? -1 : 0);
}
