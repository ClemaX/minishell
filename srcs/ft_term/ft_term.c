#include <ft_term.h>

t_term		g_term = (t_term){.pid=0};

static int	handle_status(int status)
{
	if (status & TERM_INT)
		status = term_cancel();
	if (status & TERM_EOF && g_term.line->length == 0)
		status &= ~TERM_READING;
	if (status & TERM_NEWLINE)
		status = term_new_line(status);
	if (status & TERM_CLEAR)
		term_clear_screen(status);
	if (status & TERM_STOP)
		term_stop();
	if (status & TERM_ERASE)
		term_erase();
	return ((status & (~TERM_CONSUME & ~TERM_NEWLINE)));
}

int			term_prompt(int (*exec)(const char*))
{
	int		status;

	status = TERM_READING;
	if (!term_new_line(status))
		return (-1);
	while (status & TERM_READING)
	{
		status = term_input(status);
		if (status & TERM_NEWLINE)
			exec(g_term.line->data);
		status = handle_status(status);
	}
	if (term_destroy() == -1)
		status |= TERM_ERROR;
	return ((status & TERM_ERROR) ? -1 : 0);
}

int			term_destroy(void)
{
	hist_clear(&g_term.hist);
	map_clr(&g_term.env);
	if (tcsetattr(0, 0, &g_term.s_ios_bkp) == -1)
		return (-1);
	return(0);
}
