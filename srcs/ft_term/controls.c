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

int		term_new_line(int status)
{
	term_write_prompt(status);
	if (!(status & TERM_WAITING))
	{
		if ((!g_term.hist.next || g_term.line == g_term.hist.next)
		&& !(g_term.hist.next = line_new(10)))
			return ((status | TERM_ERROR) & ~TERM_READING);
		if (g_term.line)
			hist_add(&g_term.hist, g_term.line);
		g_term.hist.next->prev = g_term.hist.last;
		*g_term.hist.next->data = '\0';
		g_term.hist.next->length = 0;
		g_term.hist.curr = g_term.hist.next;
		g_term.line = g_term.hist.next;
		g_term.cursor.x = 0;
		g_term.cursor.y = 0;
	}
	return (status & ~TERM_NEWLINE);
}

int		term_erase(int status)
{
	if (g_term.cursor.x > 0)
	{
		tputs(g_term.caps.c_left, 0, &ft_putchar);
		tputs(g_term.caps.c_del, 0, &ft_putchar);
		g_term.cursor.x--;
		status = input_special(status, g_term.line->data[g_term.cursor.x]);
		line_erase_at(g_term.line, g_term.cursor.x, 1);
	}
	return (status);
}
