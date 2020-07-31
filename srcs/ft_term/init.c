#include <ft_term.h>

static int	optional_caps(t_caps *caps)
{
	char	*area;
	int		err;

	area = NULL;
	err = !(caps->clear = tgetstr("cl", &area));
	err |= !(caps->standout = tgetstr("so", &area));
	err |= !(caps->standout_end = tgetstr("se", &area));
	err |= !(caps->c_del_n = tgetstr("ec", &area));
	return (!err);
}

static int	fatal_caps(t_caps *caps)
{
	char	*area;
	int		err;

	area = NULL;
	err = !(caps->insert = tgetstr("im", &area));
	err |= !(caps->insert_end = tgetstr("ei", &area));
	err |= !(caps->c_del = tgetstr("dc", &area));
	err |= !(caps->c_del_line = tgetstr("ce", &area));
	err |= !(caps->c_move = tgetstr("cm", &area));
	err |= !(caps->c_move_h = tgetstr("ch", &area));
	err |= !(caps->c_up = tgetstr("up", &area));
	err |= !(caps->c_down = tgetstr("do", &area));
	err |= !(caps->c_left = tgetstr("le", &area));
	err |= !(caps->c_right = tgetstr("nd", &area));
	err |= !(caps->k_up = tgetstr("ku", &area));
	err |= !(caps->k_down = tgetstr("kd", &area));
	err |= !(caps->k_left = tgetstr("kl", &area));
	err |= !(caps->k_right = tgetstr("kr", &area));
	return (!err);
}

static int	fatal_ios(t_term *t)
{
	t_map	*term_type;
	char	term_buff[MAX_ENTRY];

	if (!(term_type = map_get(t->env, "TERM"))
	|| !map_set(&t->env, "PS1", TERM_PS1)
	|| tgetent(term_buff, term_type->value) <= 0
	|| tcgetattr(0, &t->s_ios) == -1)
		return (0);
	t->s_ios_bkp = t->s_ios;
	t->s_ios.c_lflag &= ~(ICANON | ECHO | ISIG);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &t->s_ios) == -1)
		return (0);
	return (1);
}

int			term_init(t_term *t, const char **envp,
	int (*exec)(const char*, t_term*))
{

	t->pid = 0;
	t->select = (t_selection) {.start.x=-1U, .end.x=-1U};
	t->clip = (t_line) {.data=NULL, .length=0, .size=0, .prev=NULL, .next=NULL};
	t->exec = exec;
	t->st = -1;
	if (!(t->env = map_load(envp)))
		return (0);
	if (!fatal_ios(t) || !fatal_caps(&t->caps))
	{
		tcsetattr(0, 0, &t->s_ios_bkp);
		return (0);
	}
	optional_caps(&t->caps);
	ft_bzero(&t->hist, sizeof(t->hist));
	t->line = NULL;
	return (1);
}
