#include <ft_term.h>

int		term_cancel(void)
{
	selection_clear();
	*g_term.line->data = '\0';
	g_term.line->length = 0;
	return (TERM_NEWLINE | TERM_READING);
}

void	term_stop(void)
{
	if (g_term.pid != 0)
		kill(g_term.pid, SIGSTOP);
}

void	term_interrupt(int signal)
{
	if (signal == SIGINT)
	{
		if (g_term.pid)
			kill(g_term.pid, SIGINT);
		term_prewrite("\n", 1);
	}
}
