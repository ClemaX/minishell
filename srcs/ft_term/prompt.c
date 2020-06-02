#include <ft_term.h>

void		term_clear_line(void)
{

}

int			term_prompt(void)
{
	int		status;

	if (!(g_term.hist = history_add(NULL)))
		return (-1);
	status = TERM_READING;
	write(1, "minish> ", 8);
    while (status & TERM_READING)
		status = term_input(status);
	if (term_destroy() == -1)
        status |= TERM_ERROR;
	return ((status & TERM_ERROR) ? -1 : 0);
}
