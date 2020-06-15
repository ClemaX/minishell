#include <ft_term.h>

int		term_cancel(t_term *t)
{
	selection_clear(t);
	*t->line->data = '\0';
	t->line->length = 0;
	return (TERM_NEWLINE | TERM_READING);
}

void	term_stop(t_term *t)
{
	if (t->pid != 0)
		kill(t->pid, SIGSTOP);
}
