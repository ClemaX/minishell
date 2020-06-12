#include <ft_term.h>

void		term_interrupt(int signal)
{
	if (signal == SIGINT)
	{
		if (g_term.pid)
			kill(g_term.pid, SIGINT);
		term_prewrite("\n", 1);
	}
}
