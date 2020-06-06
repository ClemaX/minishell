#include <ft_term.h>

int		line_insert_at(t_line *line, size_t at, const char *str, size_t n)
{
	char	*new;
	size_t	new_len;

	if (at > line->length)
		return (0);
	new_len = line->length + n;
	if (new_len + 1 > line->size)
	{
		while (new_len + 1 > line->size)
			line->size *= 2;
		if (!(new = malloc(sizeof(*new) * line->size)))
			return (0);
		ft_strlcpy(new, line->data, line->size);
		free(line->data);
		line->data = new;
	}
	ft_memmove(line->data + at + n, line->data + at, line->length - at);
	ft_memcpy(line->data + at, str, n);
	line->length = new_len;
	line->data[line->length] = '\0';
	return (1);
}

int		line_erase(t_line *line, size_t n)
{
	if (!line || line->length < n)
		return (0);
	line->length -= n;
	line->data[line->length] = '\0';
	return (1);
}

t_line	*line_dup(t_line *line)
{
	t_line	*new;

	if (!line || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->size = line->size;
	if (!(new->data = malloc(sizeof(*new->data) * new->size)))
	{
		free(new);
		return (NULL);
	}
	ft_memcpy(new->data, line->data, line->length);
	new->length = line->length;
	new->data[new->length] = '\0';
	return (new);
}

void	line_clear(t_line **line)
{
	if (*line)
	{
		free((*line)->data);
		free(*line);
		*line = NULL;
	}
}

t_line	*line_new(size_t size)
{
	t_line	*line;

	if (!(line = malloc(sizeof(*line))))
		return (NULL);
	line->size = size;
	if (!(line->data = malloc(sizeof(*line->data) * line->size)))
	{
		free(line);
		return (NULL);
	}
	line->length = 0;
	*line->data = '\0';
	line->next = NULL;
	line->prev = NULL;
	return (line);
}
