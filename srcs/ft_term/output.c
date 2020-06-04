#include <ft_term.h>

int		term_prewrite(const char *str, size_t n)
{
	if (write(1, str, n) < 0)
		return (0);
	g_term.origin.x = n;
	g_term.origin.y = 0;
	return (1);
}

int		term_write(const char *str, size_t n)
{
	if (write(1, str, n) <= 0)
		return (0);
	g_term.cursor.x += n;
	return (line_append(g_term.line, str, n));
}

void	term_start_line(void)
{
	tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x), 0, &ft_putchar);
	g_term.cursor.x = 0;
}

void	term_erase(void)
{
	if (g_term.cursor.x > 0)
	{
		g_term.cursor.x--;
		tputs(g_term.caps.c_left, 0, &ft_putchar);
		tputs(g_term.caps.c_del, 0, &ft_putchar);
		line_erase(g_term.line, 1);
	}
}

void	term_clear_line(void)
{
	term_start_line();
	tputs(g_term.caps.c_del_line, 0, &ft_putchar);
}
