#include <tests.h>

t_term	*rand_term(unsigned line_length)
{
	static t_term	t;

	if (!(t.line = malloc(sizeof(*t.line))))
		return (NULL);
	if (line_length && !(t.line->data = rand_key(line_length)))
	{
		free(t.line);
		return(NULL);
	}
	t.line->length = line_length;
	t.cursor.pos.x = ft_rand(0, line_length);
	return (&t);
}

void	rand_term_destroy(t_term *t)
{
	free(t->line->data);
	free(t->line);
	t->line = NULL;
}
