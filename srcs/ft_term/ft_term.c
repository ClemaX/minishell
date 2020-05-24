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
	t_map	*term_type;

	signal(SIGINT, &term_interrupt);
	if (!(g_term.env = map_load(envp)))
		return (-1);
	if (!(term_type = map_get(g_term.env, "TERM"))
	|| tgetent(NULL, term_type->value) <= 0
	|| tcgetattr(0, &g_term.s_ios) == -1)
		return (-1);
	g_term.s_ios_bkp = g_term.s_ios;
	return (0);
}

int		line_append(t_line *line, char c)
{
	char	*new;
	line->length++;
	if (line->length + 1 > line->size)
	{
		line->size *= 2;
		if (!(new = malloc(sizeof(*new) * line->size)))
			return (-1);
		ft_strlcpy(new, line->data, line->size);
		free(line->data);
		line->data = new;
	}
	line->data[line->length] = '\0';
	line->data[line->length - 1] = c;
	return (1);
}

t_line	*new_line(void)
{
	t_line	*line;

	if (!(line = malloc(sizeof(*line))))
		return (NULL);
	if (!(line->data = malloc(sizeof(*line->data) * 10)))
	{
		free(line);
		return (NULL);
	}
	*line->data = '\0';
	line->length = 0;
	line->size = 10;
	return (line);
}

int		handle_special(int status, char c)
{
	if (c == '\n')
		status |= TERM_NEWLINE;
	else if (c == '"')
		status ^= TERM_D_QUOTE;
	else if (!(status & TERM_D_QUOTE) && c == '\'')
		status ^= TERM_S_QUOTE;
	else if (!(status & TERM_B_SLASH) && c == '\\')
		status &= TERM_B_SLASH;
	return (status);
}

int		read_char(int status, t_line *line)
{
	int		ret;
	char	c;

	ret = read(0, &c, 1);
	if (ret == 0)
		status &= ~TERM_READING;
	else if (ret == -1)
	{
		status &= ~TERM_READING;
		status |= TERM_ERROR;
	}
	else {
		status = handle_special(status, c);
		if (line_append(line, c) == -1)
		{
			status &= ~TERM_READING;
			status |= TERM_ERROR;
		}
	}
	return (status);
}

int		term_prompt(void)
{
	int		status;
	t_line	*history;

	if (!(history = new_line()))
		return (-1);
	status = TERM_READING;
    while ((status = read_char(status, history)) & TERM_READING)
	{
		if (status & TERM_NEWLINE)
			ft_printf("%s", history->data);
		if (status & TERM_WAITING)
			ft_printf("...");
	}
	return ((status & TERM_ERROR) ? -1 : 0);
}
