#include "abstract_dict.h"

/* TO DO:
- redirection fcts
- tokenize fct

DID:
- all builting
- store fd in parentheses
- pipe tale fd, pipe give fd
- global execution recursive loop
- redirection take fd, give fd
- exe and
- exe or
- simple cmd to execution fct
- semicolon in exe fct
- redirections exe
- simple cmd exe
- basic pipe

NOTES:
- AND/OR could fail in very specific cases (idk really)
- delete printf at the end is for debug
- have to put to 0 the flags
*/

int	execute_abstract_dict(t_op *ad, t_term *t)
{
	if (!ad || !ad->type)
	{
		return(true);
	}
	ft_dprintf(2, "[head in exec is  %p]\n", ad);
	if (ad->type & SEMICOLON)
	{
		if (ad->ch1)
			execute_cmd(ad->ch1, t);
		if (ad->ch2)
			execute_cmd(ad->ch2, t);
	}
	else if (ad->type & NONE)
		execute_cmd(ad->ch1, t);
	else
	{
		ft_printf("Something is wrong here");
	}
	return(execute_abstract_dict(ad->next, t));
}
