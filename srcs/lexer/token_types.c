/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 20:59:50 by plamtenz          #+#    #+#             */
/*   Updated: 2020/06/02 20:50:06 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define OPEN_PAR        1
#define CLOSE_PAR       2
#define T_AND           4
#define T_OR            8
#define T_PIPE          16
#define T_DGRAT         32
#define T_DLESS         64
#define T_GRAT          128
#define T_LESS          256
#define T_SEM           512

static bool parse_simple_tokens(t_token *new, const char **txt)
{
	if (!(new->data = malloc(sizeof(char) * 1)))
		return (false);
	if (*txt[0] == ';' && ft_strlcpy(new->data, *txt, 1) && (*txt)++)
		new->type = T_SEM;
	else if (*txt[0] == '(' && ft_strlcpy(new->data, *txt, 1) && (*txt)++)
		new->type = OPEN_PAR;
	else if (*txt[0] == ')' && ft_strlcpy(new->data, *txt, 1) && (*txt)++)
		new->type = CLOSE_PAR;
	else
		return (false);
	return (true);
}

static bool parse_or_pipe(t_token *new, const char **txt)
{
	if (*txt[0] == '|')
	{
		if (!ft_strncmp(*txt, "||", 2) &&
			(new->data = malloc(sizeof(char) * 2)))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_OR;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1)))
		{
			ft_strlcpy(new->data, *txt, 1);
			new->type = T_PIPE;
			(*txt)++;
		}
		else
			return (false);
		return (true);
	}
	return (false);
}

static bool parse_greather(t_token *new, const char **txt)
{
	if (*txt[0] == '>')
	{
		if (!ft_strncmp(*txt, ">>", 2) &&
			(new->data = malloc(sizeof(char) * 2)))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_DGRAT;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1)))
		{
			ft_strlcpy(new->data, *txt, 1);
			new->type = T_GRAT;
			(*txt)++;
		}
		else
			return (false);
		return(true);
	}
	return (false);
}

static bool parse_less(t_token *new, const char **txt)
{
	if (*txt[0] == '<')
	{
		if (!ft_strncmp(*txt, "<<", 2) &&
			(new->data = malloc(sizeof(char) * 2)))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_DLESS;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1)))
		{
			ft_strlcpy(new->data, *txt, 1);
			new->type = T_LESS;
			(*txt)++;
		}
		else
			return (false);
		return(true);
	}
	return (false);
}

t_token		*parse_token(const char **txt)
{
	t_token *new;

	if (!(new = malloc(sizeof(t_token))))
		return (NULL);
	if (!ft_strncmp(*txt, "&&", 2) &&
		(new->data = malloc(sizeof(char) * 2)))
	{
		ft_strlcpy(new->data, *txt, 2);
		new->type = T_AND;
		*txt += 2;
	}
	else if (parse_or_pipe(new, txt) ||
		parse_greather(new, txt) ||
		parse_less(new, txt) ||
		(ft_strchr(OPERATORS, **txt) &&
		(parse_simple_tokens(new, txt))))
		;
	else
		return (NULL);
	return (new);
}
