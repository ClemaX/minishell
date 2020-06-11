#include <ft_term.h>

char	*clip_copy(void)
{
	if (g_term.select.start.x != -1U && g_term.select.end.x != -1U)
	{
		free(g_term.clip.data);
		if (!(g_term.clip.data = ft_substr(g_term.line->data,
		g_term.select.start.x, g_term.select.end.x)))
			return (NULL);
		g_term.clip.length = g_term.select.end.x - g_term.select.start.x;
		g_term.clip.size = g_term.clip.length + 1;
		g_term.clip.next = NULL;
		g_term.clip.prev = NULL;
	}
	return (g_term.clip.data);
}

char	*clip_cut(void)
{
	if (g_term.select.start.x != -1U && g_term.select.end.x != -1U)
	{
		free(g_term.clip.data);
		g_term.clip.length = g_term.select.end.x - g_term.select.start.x;
		if (!(g_term.clip.data = ft_substr(g_term.line->data,
		g_term.select.start.x, g_term.clip.length)))
			return (NULL);
		g_term.cursor.x = g_term.select.start.x;
		tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x + g_term.cursor.x), 0, &ft_putchar);
		tputs(g_term.caps.c_del_n, g_term.clip.length, &ft_putchar);
		ft_dprintf(2, "[CLIPBD] Cut %ld chars from %s at %d\n", g_term.clip.length, g_term.line->data, g_term.cursor.x);
		line_erase_at(g_term.line, g_term.cursor.x, g_term.clip.length);
		g_term.clip.size = g_term.clip.length + 1;
		g_term.clip.next = NULL;
		g_term.clip.prev = NULL;
		selection_clear();
	}
	return (g_term.clip.data);
}

int		clip_paste(void)
{
	if (!g_term.clip.length)
		return (0);
	ft_dprintf(2, "[CLIPBD] Paste %ld chars to %s at %d\n", g_term.clip.length, g_term.line->data, g_term.cursor.x);
	term_write(g_term.clip.data, g_term.clip.length);
	return (1);
}
