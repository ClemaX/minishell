#include <ft_term.h>

t_term g_term = (t_term){.pid=0};

void	term_interrupt(int signal) {
	if (signal == SIGINT)
	{
		if (g_term.pid)
			kill(g_term.pid, SIGINT);
		write(0, "\n", 1);
	}
}

int		term_init(const char **envp)
{
	t_map		*term_type;

	signal(SIGINT, &term_interrupt);
	if (!(g_term.env = map_load(envp)))
		return (-1);
	if (!(term_type = map_get(g_term.env, "TERM"))
	|| tcgetattr(0, &g_term.s_ios) == -1)
		return (-1);
	g_term.s_ios_bkp = g_term.s_ios;
	return (0);
}

int		term_destroy(void)
{
	if (tcsetattr(0, 0, &g_term.s_ios_bkp) == -1)
		return (-1);
	history_clear(&g_term.hist);
	map_clr(&g_term.env);
	return(0);
}
