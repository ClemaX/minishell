#include <tests.h>

t_list	*lst_add_front(t_list **list, void *data)
{
	t_list	*new;

	if (!(new = malloc(sizeof(*new))))
		return (NULL);
	new->content = data;
	new->next = *list;
	return ((*list = new));
}

void	lst_clear(t_list **list)
{
	t_list	*curr;

	while ((curr = *list))
	{
		*list = curr->next;
		free(curr->content);
		free(curr);
	}
}
