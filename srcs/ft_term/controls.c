#include <ft_term.h>

int		term_erase(t_term *t, int status)
{
	if (t->cursor.pos.x > 0)
	{
		tputs(t->caps.c_left, 0, &ft_putchar);
		tputs(t->caps.c_del, 0, &ft_putchar);
		t->cursor.pos.x--;
		line_erase_at(t->line, t->cursor.pos.x, 1);
	}
	return (status);
}
