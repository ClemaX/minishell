#include <ft_term.h>

int		term_erase(int status)
{
	if (g_term.cursor.x > 0)
	{
		tputs(g_term.caps.c_left, 0, &ft_putchar);
		tputs(g_term.caps.c_del, 0, &ft_putchar);
		g_term.cursor.x--;
		line_erase_at(g_term.line, g_term.cursor.x, 1);
	}
	return (status);
}
