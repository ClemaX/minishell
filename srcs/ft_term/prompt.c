#include <ft_term.h>

void	term_write_prompt(t_term *t, int status)
{
	if (status & TERM_WAITING)
		term_prewrite(t, "> ", 2);
	else
		term_prewrite(t, TERM_PS1, sizeof(TERM_PS1) - 1);
}

int		parse_line(t_term *t, int status)
{
	size_t	i;

	status &= ~TERM_WAITING;
	i = 0;
	while (i < t->line->length)
	{
		if (status & TERM_B_SLASH)
			status &= ~TERM_B_SLASH;
		else if (!(status & TERM_S_QUOTE) && t->line->data[i] == '"')
			status ^= TERM_D_QUOTE;
		else if (!(status & TERM_D_QUOTE) && t->line->data[i] == '\'')
			status ^= TERM_S_QUOTE;
		else if (!(status & TERM_B_SLASH) && t->line->data[i] == '\\')
			status |= TERM_B_SLASH;
		i++;
	}
	return (status);
}

// TODO: Refactor and separate line init
int		term_new_line(t_term *t, int status)
{
	term_end_line(t);
	selection_clear(t);
	if (t->line && (status = parse_line(t, status)) & TERM_WAITING)
		term_write(t, "\n", 1);
	if (!(status & TERM_WAITING))
	{
		if (t->line)
		{
			tputs(t->caps.insert_end, 0, &ft_putchar);
			write(1, "\n", 1);
			t->exec(t->line->data, t);
			tputs(t->caps.insert, 0, &ft_putchar);
		}
		if ((!t->hist.next || t->line == t->hist.next)
		&& !(t->hist.next = line_new(10)))
			return ((status | TERM_ERROR) & ~TERM_READING);
		if (t->line)
			hist_add(&t->hist, t->line);
		t->hist.next ->prev = t->hist.last;
		*t->hist.next->data = '\0';
		t->hist.next->length = 0;
		t->hist.curr = t->hist.next;
		t->line = t->hist.next;
		t->cursor.pos.x = 0;
		t->cursor.pos.y = 0;
	}
	term_write_prompt(t, status);
	return (status & ~TERM_NEWLINE);
}
