#include <ft_term.h>

void	term_up(void)
{
	if (g_term.hist.curr->prev)
	{
		if (g_term.hist.curr != g_term.hist.next && g_term.line->length)
		{
			hist_commit(&g_term.hist, g_term.line);
			free(g_term.line);
		}
		g_term.hist.curr = g_term.hist.curr->prev;
		term_clear_line();
		write(1, g_term.hist.curr->data, g_term.hist.curr->length);
		g_term.line = line_dup(g_term.hist.curr);
		g_term.cursor.x = g_term.hist.curr->length;
	}
}

void	term_down(void)
{
	if (g_term.hist.curr->next)
	{
		if (g_term.hist.curr != g_term.hist.next)
		{
			hist_commit(&g_term.hist, g_term.line);
			free(g_term.line);
		}
		g_term.hist.curr = g_term.hist.curr->next;
		term_clear_line();
		write(1, g_term.hist.curr->data, g_term.hist.curr->length);
		g_term.line = line_dup(g_term.hist.curr);
		g_term.cursor.x = g_term.hist.curr->length;
	}
}

void	term_left(void)
{
	if (g_term.cursor.x > 0)
	{
		g_term.cursor.x--;
		tputs(g_term.caps.c_left, 0, &ft_putchar);
	}
}

void	term_right(void)
{
	if (g_term.cursor.x < g_term.line->length)
	{
		g_term.cursor.x++;
		tputs(g_term.caps.c_right, 0, &ft_putchar);
	}
}
