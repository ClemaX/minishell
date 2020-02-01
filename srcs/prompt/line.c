/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/21 21:25:00 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 05:22:10 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <line.h>
#include <limits.h>

/*
**	line:		The line to add content on
**	c:			The character to add
**
**	Add a character to the line elements list
*/

t_line	*line_add(t_line **line, char c)
{
	t_line *new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->c = c;
	new->next = *line;
	return ((*line = new));
}

/*
**	line:		The line to clear
**
**	Free every list element of the line and set its pointer to NULL
*/

t_line	*line_clr(t_line **line)
{
	t_line	*curr;

	while ((curr = *line))
	{
		*line = (*line)->next;
		free(curr);
	}
	return (NULL);
}

/*
**	line:		The line to measure
**
**	Get the total length of a line
*/

int		line_len(t_line *line)
{
	t_line	*curr;
	int		len;

	len = 0;
	curr = line;
	while (curr)
	{
		len++;
		curr = curr->next;
	}
	return (len);
}

/*
**	dest:		The destination string
**	line:		The line to copy
**
**	Copy a line into a string and return it's length
**	Note: Returns -1 in case of error
*/

int		line_put(char **dest, t_line **line, char clr)
{
	const int	len = line_len(*line);
	t_line		*curr;

	if (!(*dest = malloc(sizeof(*dest) * (len + 1))))
	{
		if (clr)
			line_clr(line);
		return (-1);
	}
	*dest += len;
	**dest = '\0';
	curr = *line;
	while (curr)
	{
		*--(*dest) = curr->c;
		curr = curr->next;
	}
	if (clr)
		line_clr(line);
	return (len);
}

char	*line_cat(t_line **line, char clr)
{
	char	*str;
	int		len;

	if ((len = line_put(&str, line, clr)) == -1)
		return (NULL);
	return (str);
}
