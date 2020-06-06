#include <ft_term.h>

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
			g_term.select.start.x = g_term.cursor.x;
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
			g_term.select.start.x = g_term.cursor.x;
		}
	}
}
