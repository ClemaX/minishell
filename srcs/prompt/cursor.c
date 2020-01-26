/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cursor.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/25 15:33:02 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 20:46:54 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <libft.h>
#include <stdlib.h>

t_line	*del_line(t_line *curr, int min, int max, int i)
{
	t_line	*next;

	if (!curr)
		return (NULL);
	if (i >= min && i <= max)
	{
		next = curr->next;
		free(curr);
		return (next);
	}
	curr->next = del_line(curr->next, min, max, i + 1);
	return (curr);
}

void	cursor_del_range(t_term *term, int min, int max)
{
	int		new_x;
	int		len;

	if (!term->line || !term->line->line || min > max)
		return ;
	new_x = term->cursor.x - (max - min);
	if (!(new_x >= 0 && new_x <= term->cursor.max.x))
		return ;
	term->cursor.x = new_x;
	term->cursor.max.x -= max - min;
	tputs(tgoto(term->caps.ch, 0, new_x + 9), 1, &ft_putchar);
	tputs(term->caps.dc_n, max - min, &ft_putchar);
	len = line_len(term->line->line);
	term->line->line = del_line(term->line->line, len - max, len - min, 0);
}
