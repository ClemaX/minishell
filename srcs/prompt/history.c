/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   history.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/19 21:31:26 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/23 19:17:46 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <prompt.h>
#include <stdlib.h>

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
