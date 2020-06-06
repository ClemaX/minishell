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
	if (write(1, str, n) <= 0
	|| !(line_insert_at(g_term.line, g_term.cursor.x, str, n)))
		return (0);
	g_term.cursor.x += n;
	return (1);
}

void	term_start_line(void)
{
	tputs(tgoto(g_term.caps.c_move_h, 0, g_term.origin.x), 0, &ft_putchar);
	g_term.cursor.x = 0;
}

void	term_clear_line(void)
{
	term_start_line();
	tputs(g_term.caps.c_del_line, 0, &ft_putchar);
}

void	term_clear_screen(int status)
{
	tputs(g_term.caps.clear, 0, &ft_putchar);
	if (status & TERM_WAITING)
		term_prewrite("> ", 2);
	else
		term_prewrite("minish> ", 8);
	write(1, g_term.line->data, g_term.line->length);
	g_term.cursor.x = g_term.line->length;
}
