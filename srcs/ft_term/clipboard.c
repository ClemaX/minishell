#include <ft_term.h>

char	*clip_copy(t_term *t)
{
	if (t->select.start.x != -1U && t->select.end.x != -1U)
	{
		free(t->clip.data);
		t->clip.length = t->select.end.x - t->select.start.x;
		if (!(t->clip.data = ft_substr(t->line->data,
		t->select.start.x, t->clip.length)))
			return (NULL);
		t->cursor.pos.x = t->select.start.x;
		t->clip.size = t->clip.length + 1;
		t->clip.next = NULL;
		t->clip.prev = NULL;
	}
	return (t->clip.data);
}

char	*clip_cut(t_term *t)
{
	if (t->select.start.x != -1U && t->select.end.x != -1U)
	{
		if (!clip_copy(t))
			return (NULL);
		tputs(tgoto(t->caps.c_move_h, 0, t->cursor.origin.x + t->cursor.pos.x),
			0, &ft_putchar);
		tputs(t->caps.c_del_n, t->clip.length, &ft_putchar);
		ft_dprintf(2, "[CLIPBD] Cut %ld chars from %s at %d\n", t->clip.length,
			t->line->data, t->cursor.pos.x);
		line_erase_at(t->line, t->cursor.pos.x, t->clip.length);
		selection_clear(t);
	}
	return (t->clip.data);
}

int		clip_paste(t_term *t)
{
	if (!t->clip.length)
		return (0);
	selection_clear(t);
	ft_dprintf(2, "[CLIPBD] Paste %ld chars to %s at %d\n", t->clip.length,
		t->line->data, t->cursor.pos.x);
	term_write(t, t->clip.data, t->clip.length);
	return (1);
}

void	clip_clear(t_line *clip)
{
	free(clip->data);
	clip->data = NULL;
}
