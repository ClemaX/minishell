/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/17 21:12:29 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/17 22:29:47 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <parser.h>

char	check_type(t_token **token, t_type type, char **buffer)
{
	int	data_size;

	if (!token)
		return (0);
	if ((*token)->type == type)
	{
		if (buffer)
		{
			data_size = ft_strlen((*token)->data) + 1;
			if (!(*buffer = malloc(sizeof(char) * data_size)))
				return (0);
			ft_strlcpy(*buffer, (*token)->data, data_size);
		}
		*token = (*token)->next;
		return (1);
	}
	*token = (*token)->next;
	return (0);
}
