/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   arg_utils.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/15 17:40:37 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/15 17:45:06 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>

int	arg_check(char *key)
{
	while (*key)
	{
		if (!((ft_isalnum(*key)) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}
