#include <ft_term.h>

void	hist_add(t_hist *hist, t_line *line)
{
	if (hist->last)
		hist->last->next = line;
	line->prev = hist->last;
	hist->last = line;
	hist->last->next = hist->next;
}

void	hist_clear(t_hist *hist)
{
	t_line	*curr;

	free(hist->next);
	while ((curr = hist->last))
	{
		hist->last = curr->prev;
		line_clear(&curr);
	}
}

void	hist_commit(t_hist *hist, t_line *line)
{
	free(hist->curr->data);
	hist->curr->data = line->data;
	hist->curr->length = line->length;
	hist->curr->size = line->size;
}

void	hist_pop(t_hist *hist)
{
	t_line	*prev;

	if (hist->last)
	{
		prev = hist->last->prev;
		line_clear(&hist->last);
		hist->last = prev;
	}
}
