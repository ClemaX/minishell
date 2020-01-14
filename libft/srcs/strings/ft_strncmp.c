/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:20:47 by chamada           #+#    #+#             */
/*   Updated: 2020/01/14 05:37:38 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, t_size n)
{
	if (!n)
		return (0);
	while (n-- > 1 && *s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
