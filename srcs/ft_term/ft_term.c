#include <ft_term.h>

t_term g_term = (t_term){.pid=0};

void	term_interrupt(int signal) {
	if (signal == SIGINT)
	{
		if (g_term.pid)
			kill(g_term.pid, SIGINT);
		write(1, "\n", 1);
	}
}

static int	init_caps()
{
	char	*area;

	area = NULL;
	return ((g_term.caps.c_del = tgetstr("dc", &area))
	&& (g_term.caps.c_up = tgetstr("up", &area))
	&& (g_term.caps.c_down = tgetstr("do", &area))
	&& (g_term.caps.c_left = tgetstr("le", &area))
	&& (g_term.caps.c_right = tgetstr("nd", &area))
	&& (g_term.caps.k_up = tgetstr("ku", &area))
	&& (g_term.caps.k_down = tgetstr("kd", &area))
	&& (g_term.caps.k_left = tgetstr("kl", &area))
	&& (g_term.caps.k_right = tgetstr("kr", &area)));
}

int		term_init(const char **envp)
{
	t_map		*term_type;
	char		term_buff[MAX_ENTRY];

	signal(SIGINT, &term_interrupt);
	if (!(g_term.env = map_load(envp)))
		return (-1);
	if (!(term_type = map_get(g_term.env, "TERM"))
	|| tgetent(term_buff, term_type->value) <= 0
	|| tcgetattr(0, &g_term.s_ios) == -1)
		return (-1);
	g_term.s_ios_bkp = g_term.s_ios;
	g_term.s_ios.c_lflag &= ~(ICANON | ECHO | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_term.s_ios) == -1
	|| !init_caps())
		return (-1);
	return (0);
}

int		term_destroy(void)
{
	history_clear(&g_term.hist);
	map_clr(&g_term.env);
	if (tcsetattr(0, 0, &g_term.s_ios_bkp) == -1)
		return (-1);
	return(0);
}
