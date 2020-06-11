#include <ft_term.h>

void	term_write_prompt(int status)
{
	if (status & TERM_NEWLINE)
		term_prewrite("\n", 1);
	if (status & TERM_WAITING)
		term_prewrite("> ", 2);
	else
		term_prewrite(TERM_PS1, sizeof(TERM_PS1) - 1);
}
