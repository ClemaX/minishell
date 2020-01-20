/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   variables.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 02:53:18 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 03:37:46 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <map.h>
#include <token.h>
#include <libft.h>
#include <stdlib.h>

int		key_check(char *key)
{
	while (*key)
	{
		if (!((ft_isalnum(*key)) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

int	var_assign(t_token *token, void *env)
{
	char	*c;

	if ((c = ft_strchr(token->data, '=')))
	{
		*c = '\0';
		if (!key_check(token->data))
		{
			*c = '=';
			return (0);
		}
		if (!(map_set((t_map**)env, token->data, c + 1)))
		{
			*c = '=';
			return (-1);
		}
		*token->data = '\0';
		return (1);
	}
	return (0);
}

int	var_expand(t_token *token, void *env)
{
	char	*c;
	char	*join;
	t_map	*var;

	if ((c = ft_strchr(token->data, '$')) && key_check(c + 1))
	{
		*c = '\0';
		if ((var = map_get(*((t_map**)env), c + 1)))
		{
			if (!(join = ft_strjoin(token->data, var->value)))
				return (-1);
			free(token->data);
			token->data = join;
		}
		return (1);
	}
	return (0);
}
