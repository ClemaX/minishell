#include <ft_term.h>

static int	handle_status(t_term *t, int status)
{
	if (status & TERM_INT)
		status = term_cancel(t);
	if (status & TERM_EOF && t->line->length == 0)
		status &= ~TERM_READING;
	if (status & TERM_NEWLINE)
		status = term_new_line(t, status);
	if (status & TERM_CLEAR)
		term_clear_screen(t, status);
	if (status & TERM_STOP)
		term_stop(t);
	if (status & TERM_ERASE)
		status = term_erase(t, status);
	return ((status & (~TERM_CONSUME & ~TERM_NEWLINE)));
}

int			term_prompt(const char **envp, int (*exec)(const char*))
{
	int		status;
	t_term	term;

	status = TERM_READING;
	if (!term_init(&term, envp, exec) || !term_new_line(&term, status))
		return (-1);
	tputs(term.caps.insert, 0, &ft_putchar);
	while (status & TERM_READING)
		status = handle_status(&term, term_input(&term, status));
	if (term_destroy(&term) == -1)
		status |= TERM_ERROR;
	tputs(term.caps.insert_end, 0, &ft_putchar);
	return ((status & TERM_ERROR) ? -1 : 0);
}

int			term_destroy(t_term *t)
{
	hist_clear(&t->hist);
	map_clr(&t->env);
	line_clear(&t->line);
	clip_clear(&t->clip);
	if (tcsetattr(0, 0, &t->s_ios_bkp) == -1)
		return (-1);
	return(0);
}
