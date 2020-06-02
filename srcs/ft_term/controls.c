#include <ft_term.h>

int		term_cancel(void)
{
	write(1, "\n", 1);
	*g_term.hist->data = '\0';
	g_term.hist->length = 0;
	return (TERM_NEWLINE | TERM_READING);
}

void	term_new_line(int status)
{
	g_term.hist = history_add(g_term.hist);
	if (status & TERM_WAITING)
		write(1, "> ", 2);
	else
		write(1, "minish> ", 8);
}

void	term_stop(void)
{
	if (g_term.pid != 0)
		kill(g_term.pid, SIGSTOP);
}

void	term_erase(void)
{
	tputs(g_term.caps.c_left, 0, &ft_putchar);
	tputs(g_term.caps.c_del, 0, &ft_putchar);
}
