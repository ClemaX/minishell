#include <ft_term.h>

void	highlight(t_selection *select)
{
	if (select->start.x != -1U && select->end.x != -1U)
	{
		ft_dprintf(2, "[SELECT] start: %d, end: %d\n", select->start.x, select->end.x);
		tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x), 0, &ft_putchar);
		tputs(g_term.caps.c_del_line, 0, &ft_putchar);
		write(1, g_term.line->data, select->start.x);
		tputs(g_term.caps.standout, 0, &ft_putchar);
		write(1, g_term.line->data + select->start.x, select->end.x - select->start.x);
		tputs(g_term.caps.standout_end, 0, &ft_putchar);
		write(1, g_term.line->data + select->end.x, g_term.line->length - select->end.x);
		tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x + g_term.cursor.x), 0, &ft_putchar);
	}
}

void	selection_left(void)
{
	if (g_term.cursor.x > 0)
	{
		if (g_term.select.start.x == -1U || g_term.select.end.x == -1U)
		{
			g_term.select.start.x = g_term.cursor.x;
			g_term.select.end.x = g_term.cursor.x;
		}
		else
		{
			term_left();
			if (g_term.select.start.x == g_term.cursor.x + 1)
				g_term.select.start.x = g_term.cursor.x;
			else
				g_term.select.end.x = g_term.cursor.x;
			highlight(&g_term.select);
		}
	}
}

void	selection_right(void)
{
	if (g_term.cursor.x < g_term.line->length)
	{
		if (g_term.select.start.x == -1U || g_term.select.end.x == -1U)
		{
			g_term.select.start.x = g_term.cursor.x;
			g_term.select.end.x = g_term.cursor.x;
		}
		else
		{
			term_right();
			if (g_term.select.end.x == g_term.cursor.x - 1)
				g_term.select.end.x = g_term.cursor.x;
			else
				g_term.select.start.x = g_term.cursor.x;
			highlight(&g_term.select);
		}
	}
}

void	selection_clear(void)
{
	if (g_term.select.start.x != -1U || g_term.select.end.x != -1U)
	{
		ft_dprintf(2, "[SELECT] clear\n");
		g_term.select = (t_selection){.start.x=-1U, .end.x=-1U};
		if (g_term.line)
		{
			tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x), 0, &ft_putchar);
			tputs(g_term.caps.c_del_line, 0, &ft_putchar);
			write(1, g_term.line->data,  g_term.line->length);
			tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x + g_term.cursor.x), 0, &ft_putchar);
		}
	}
}
