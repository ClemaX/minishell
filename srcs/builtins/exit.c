#include "builtins.h"

int		ft_exit(t_term *t)
{
	term_destroy(t);
	write(1, "exit\n", 5);
	tputs(t->caps.insert_end, 0, &ft_putchar);
	ft_dprintf(2, "exiting with status code %d", t->st);
	exit(t->st);
	return (t->st);
}
