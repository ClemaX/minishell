/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 02:53:21 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 05:33:36 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <token.h>
#include <stdlib.h>

int	token_foreach(t_token *tokens, void *param, int (f)(t_token*, void*))
{
	t_token	*curr;
	int		ret;

	curr = tokens;
	ret = 0;
	while (curr && (ret = f(curr, param)) != -1)
		curr = curr->next;
	return (ret == -1 ? -1 : 1);
}

t_token	*token_add(t_token **tokens, char *data, t_token_t type)
{
	t_token	*last;
	t_token *new;

	if (!data || !(new = malloc(sizeof(*new))))
		return (NULL);
	new->data = data;
	new->next = NULL;
	new->type = type;
	if (!*tokens)
		return (*tokens = new);
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
	return (new);
}