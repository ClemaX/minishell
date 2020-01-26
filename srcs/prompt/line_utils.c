/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 20:55:47 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 19:01:59 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <line.h>
#include <libft.h>
#include <stdlib.h>

static char	*char_dup(char c)
{
	char	*res;

	if (!(res = malloc(sizeof(char))))
		return (NULL);
	*res = c;
	return (res);
}

void	line_insert_at(t_line **line, int pos, char *str)
{
	t_line	*curr;
	t_line	*start;
	t_line	*ret;
	int		len;
	int		i;

	if (!*line || !(len = line_len(*line))
	|| (i = len - pos) == 0)
		while (*str)
			line_add(line, char_dup(str++), 1);
	else
	{
		start = *line;
		while (--i > 0)
			start = start->next;
		curr = start->next;
		while (*str)
			line_add(&curr, char_dup(str++), 1);
		start->next = curr;
	}
}

char	*line_get_range(t_line *line, int min, int max)
{
	char	*str;
	int		len;
	t_line	*curr;

	len = line_len(line);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	curr = line;
	str += len;
	*str = 0;
	while (curr)
	{
		str -= curr->size;
		ft_memcpy(str, curr->content, curr->size);
		curr = curr->next;
	}
	return (str);
}
