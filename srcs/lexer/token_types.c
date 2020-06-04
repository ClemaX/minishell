
#include "lexer.h"

static bool parse_simple_tokens(t_token *new, const char **txt)
{
	if (!(new->data = malloc(sizeof(char) * 1 + 1)) && !(new->data[1] = 0))
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

#include "stdio.h"

static bool parse_or_pipe(t_token *new, const char **txt)
{
	if (*txt[0] == '|')
	{
		if (!ft_strncmp(*txt, "||", 2) && (((*txt)[2] && (*txt)[2] != '|') ||
			!(*txt)[2]) &&
			((new->data = malloc(sizeof(char) * 2 + 1)) && !(new->data[2] = 0)))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_OR;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1 + 1)) && !(new->data[1] = 0))
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
		if (!ft_strncmp(*txt, ">>", 2) && (((*txt)[2] && (*txt)[2] != '>' ) ||
			!(*txt)[2]) &&
			(new->data = malloc(sizeof(char) * 2 + 1)) && !(new->data[2] = 0))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_DGRAT;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1 + 1)) && !(new->data[1] = 0))
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
		if (!ft_strncmp(*txt, "<<", 2) && (((*txt)[2] && (*txt)[2] != '<') ||
			!(*txt)[2]) &&
			(new->data = malloc(sizeof(char) * 2 + 1)) && !(new->data[2] = 0))
		{
			ft_strlcpy(new->data, *txt, 2);
			new->type = T_DLESS;
			*txt += 2;
		}
		else if ((new->data = malloc(sizeof(char) * 1 + 1)) && !(new->data[1] = 0))
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
		(new->data = malloc(sizeof(char) * 2 + 1)) && !(new->data[2] = 0))
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
	{
		free(new);
		return (NULL);
	}
	return (new);
}
