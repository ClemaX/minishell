#include <ft_term.h>

static int	init_caps()
{
	char	*area;
	int		err;

	area = NULL;
	err = !(g_term.caps.insert = tgetstr("im", &area));
	err |= !(g_term.caps.insert_end = tgetstr("ei", &area));
	err |= !(g_term.caps.clear = tgetstr("cl", &area));
	err |= !(g_term.caps.standout = tgetstr("so", &area));
	err |= !(g_term.caps.standout_end = tgetstr("se", &area));
	err |= !(g_term.caps.m_blink = tgetstr("mb", &area));
	err |= !(g_term.caps.m_end = tgetstr("me", &area));
	err |= !(g_term.caps.c_del = tgetstr("dc", &area));
	err |= !(g_term.caps.c_del_line = tgetstr("ce", &area));
	err |= !(g_term.caps.c_move = tgetstr("cm", &area));
	err |= !(g_term.caps.c_move_h = tgetstr("ch", &area));
	err |= !(g_term.caps.c_up = tgetstr("up", &area));
	err |= !(g_term.caps.c_down = tgetstr("do", &area));
	err |= !(g_term.caps.c_left = tgetstr("le", &area));
	err |= !(g_term.caps.c_left_n = tgetstr("LE", &area));
	err |= !(g_term.caps.c_right = tgetstr("nd", &area));
	err |= !(g_term.caps.k_up = tgetstr("ku", &area));
	err |= !(g_term.caps.k_down = tgetstr("kd", &area));
	err |= !(g_term.caps.k_left = tgetstr("kl", &area));
	err |= !(g_term.caps.k_right = tgetstr("kr", &area));
	return (!err);
}

int			term_init(const char **envp)
{
	t_map	*term_type;
	char	term_buff[MAX_ENTRY];

	signal(SIGINT, &term_interrupt);
	if (!(g_term.env = map_load(envp)))
		return (-1);
	if (!(term_type = map_get(g_term.env, "TERM"))
	|| !map_set(&g_term.env, "PS1", TERM_PS1)
	|| tgetent(term_buff, term_type->value) <= 0
	|| tcgetattr(0, &g_term.s_ios) == -1)
		return (-1);
	g_term.s_ios_bkp = g_term.s_ios;
	g_term.s_ios.c_lflag &= ~(ICANON | ECHO | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_term.s_ios) == -1)
		return (-1);
	init_caps();
	ft_bzero(&g_term.hist, sizeof(g_term.hist));
	g_term.line = NULL;
	return (0);
}
