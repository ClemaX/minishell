/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 20:55:47 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 18:57:05 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <line.h>
#include <libft.h>
#include <stdlib.h>

void	line_insert_at(t_line **line, int pos, char *str)
{
	t_line	*curr;
	t_line	*start;
	int		len;
	int		i;

	if (!*line || !(len = line_len(*line))
	|| (i = len - pos) == 0)
		while (*str)
			line_add(line, *str++);
	else
	{
		start = *line;
		while (--i > 0)
			start = start->next;
		curr = start->next;
		while (*str)
			line_add(&curr, *str++);
		start->next = curr;
	}
}

char	*line_get_range(t_line *line, int min, int max)
{
	char	*str;
	int		len;
	t_line	*curr;

	(void)min;
	(void)max;
	len = line_len(line);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	curr = line;
	str += len;
	*str = 0;
	while (curr)
	{
		*--str = curr->c;
		curr = curr->next;
	}
	return (str);
}

t_line	*line_dup(t_line *line)
{
	t_line	*dup;
	t_line	*new;

	if (!line || !(new = malloc(sizeof(*new))))
		return (NULL);
	dup = new;
	new->c = line->c;
	while ((line = line->next))
	{
		if (!(new->next = malloc(sizeof(*new))))
			return (line_clr(&dup));
		new = new->next;
		new->c = line->c;
	}
	new->next = NULL;
	return (dup);
}