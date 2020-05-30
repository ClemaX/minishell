#include <ft_term.h>

t_line	*history_add(t_line *prev)
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
	line->next = NULL;
	line->prev = prev;
	if (prev)
		prev->next = line;
	return (line);
}

void    history_clear(t_line **hist)
{
    t_line  *curr;

    while ((curr = *hist))
    {
        *hist = curr->next;
        line_clear(&curr);
    }
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

void    line_clear(t_line **line)
{
    if (*line)
    {
        free((*line)->data);
        free(*line);
        *line = NULL;
    }
}
