/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:31:26 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 03:29:11 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>
#include <libft.h>

t_history	*history_add(t_history **history)
{
	t_history	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->line = NULL;
	new->prev = *history;
	if (new->prev)
		new->prev->next = new;
	new->next = NULL;
	return (*history = new);
}

void		history_clr(t_history **history)
{
	t_history	*curr;

	while ((curr = *history))
	{
		*history = curr->prev;
		free(curr->line);
		free(curr);
	}
}

void		history_prev(t_term *term)
{
	if (term->current)
	{
		line_clr(&term->line);
		term->line = line_dup(term->current->line);
		term->current = term->current->prev;
		term_clear_line(term);
		term->cursor.x = line_len(term->line);
		term->cursor.max.x = term->cursor.x;
		ft_printf("%s", line_cat(&term->line, 0));
	}
}

void		history_next(t_term *term)
{
	if (term->current)
	{
		line_clr(&term->line);
		term->line = line_dup(term->current->line);
		term->current = term->current->next;
		term_clear_line(term);
		term->cursor.x = line_len(term->line);
		term->cursor.max.x = term->cursor.x;
		ft_printf("%s", line_cat(&term->line, 0));
	}
}
