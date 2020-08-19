#include <tests.h>

t_term	*rand_term(unsigned line_length)
{
	static t_term	t;

	rand_term_destroy(&t);
	if (!(t.line = malloc(sizeof(*t.line))))
		return (NULL);
	t.line->data = NULL;
	if (!(t.line->data = rand_key(line_length)))
	{
		free(t.line);
		return(NULL);
	}
	t.line->length = line_length;
	t.line->size = line_length + 1;
	t.cursor.pos.x = ft_rand(0, line_length);
	return (&t);
}

void	rand_term_destroy(t_term *t)
{
	if (t->line)
	{
		free(t->line->data);
		free(t->line);
	}
	if (t->clip.size)
	{
		free(t->clip.data);
		ft_bzero(&t->clip, sizeof(t->clip));
	}
	ft_bzero(t, sizeof(*t));
	t->select = (t_selection){.start = {.x = -1U, .y = -1U},\
		.end = {.x = -1U, .y = -1U}};
}
