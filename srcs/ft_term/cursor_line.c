#include <ft_term.h>

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

void	term_start_line(void)
{
	tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x), 0, &ft_putchar);
	g_term.cursor.x = 0;
}

void	term_end_line(void)
{
	if (g_term.line && g_term.line->length)
	{
		g_term.cursor.x = g_term.line->length;
		tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x + g_term.cursor.x), 0, &ft_putchar);
	}
}
