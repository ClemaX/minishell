#include <ft_term.h>

void	term_up(t_term *t)
{
	if (t->hist.curr->prev)
	{
		if (t->hist.curr != t->hist.next && t->line->length)
		{
			hist_commit(&t->hist, t->line);
			free(t->line);
		}
		t->hist.curr = t->hist.curr->prev;
		term_clear_line(t);
		write(1, t->hist.curr->data, t->hist.curr->length);
		t->line = line_dup(t->hist.curr);
		t->cursor.pos.x = t->hist.curr->length;
	}
}

void	term_down(t_term *t)
{
	if (t->hist.curr->next)
	{
		if (t->hist.curr != t->hist.next)
		{
			hist_commit(&t->hist, t->line);
			free(t->line);
		}
		t->hist.curr = t->hist.curr->next;
		term_clear_line(t);
		write(1, t->hist.curr->data, t->hist.curr->length);
		t->line = line_dup(t->hist.curr);
		t->cursor.pos.x = t->hist.curr->length;
	}
}
