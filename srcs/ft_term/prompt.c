#include <ft_term.h>

void	term_write_prompt(int status)
{
	if (status & TERM_NEWLINE)
		term_prewrite("\n", 1);
	if (status & TERM_WAITING)
		term_prewrite("> ", 2);
	else
		term_prewrite(TERM_PS1, sizeof(TERM_PS1) - 1);
}

int		parse_line(int status)
{
	size_t	i;

	status &= ~TERM_WAITING;
	i = 0;
	while (i < g_term.line->length)
	{
		if (status & TERM_B_SLASH)
			status &= ~TERM_B_SLASH;
		else if (!(status & TERM_S_QUOTE) && g_term.line->data[i] == '"')
			status ^= TERM_D_QUOTE;
		else if (!(status & TERM_D_QUOTE) && g_term.line->data[i] == '\'')
			status ^= TERM_S_QUOTE;
		else if (!(status & TERM_B_SLASH) && g_term.line->data[i] == '\\')
			status |= TERM_B_SLASH;
		i++;
	}
	return (status);
}

int		term_new_line(int status)
{
	term_end_line();
	selection_clear();
	if (g_term.line && (status = parse_line(status)) & TERM_WAITING)
		term_write("\n", 1);
	term_write_prompt(status);
	if (!(status & TERM_WAITING))
	{
		if (g_term.line)
		{
			tputs(g_term.caps.insert_end, 0, &ft_putchar);
			g_term.exec(g_term.line->data);
			tputs(g_term.caps.insert, 0, &ft_putchar);
		}
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
