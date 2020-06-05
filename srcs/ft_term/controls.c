#include <ft_term.h>

int		term_cancel(void)
{
	write(1, "\n", 1);
	*g_term.line->data = '\0';
	g_term.line->length = 0;
	return (TERM_NEWLINE | TERM_READING);
}

void	term_stop(void)
{
	if (g_term.pid != 0)
		kill(g_term.pid, SIGSTOP);
}

int		term_new_line(int status)
{
	if ((!g_term.hist.next || g_term.line == g_term.hist.next)
	&& !(g_term.hist.next = line_new(10)))
		return ((status | TERM_ERROR) & ~TERM_READING);
	if (g_term.line != NULL)
		hist_add(&g_term.hist, g_term.line);
	g_term.hist.next->prev = g_term.hist.last;
	*g_term.hist.next->data = '\0';
	g_term.hist.next->length = 0;
	g_term.hist.curr = g_term.hist.next;
	g_term.line = g_term.hist.next;
	if (status & TERM_WAITING)
		term_prewrite("> ", 2);
	else
		term_prewrite("minish> ", 8);
	g_term.cursor.x = 0;
	g_term.cursor.y = 0;
	return (status & ~TERM_NEWLINE);
}

void	term_erase(void)
{
	if (g_term.cursor.x > 0)
	{
		g_term.cursor.x--;
		tputs(g_term.caps.c_left, 0, &ft_putchar);
		tputs(g_term.caps.c_del, 0, &ft_putchar);
		line_erase(g_term.line, 1);
	}
}
