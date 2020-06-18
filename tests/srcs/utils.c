/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:34:23 by chamada           #+#    #+#             */
/*   Updated: 2020/06/15 21:08:43 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int		run_tests(char *label, int (*tests[])(void), int iterations)
{
	int	ret;
	int err;
	int i;
	int test_i;

	printf("%s %*s\t",
		BULLET, LBL_FW, label);
	test_i = 0;
	err = 0;
	while (tests[test_i])
	{
		i = 0;
		while (i++ < iterations)
		{
			ret = (*tests[test_i])();
			printf(ret ? PASS : FAIL);
			err += !ret;
		}
		test_i++;
		if (tests[test_i])
			printf(" ");
	}
	printf("\n");
	return (!err);
}

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
