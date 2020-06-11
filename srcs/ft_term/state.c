#include <ft_term.h>

int	input_special(int status, char c)
{
	if (status & TERM_B_SLASH)
		return (status & ~TERM_B_SLASH);
	if (c == '\n')
		status |= TERM_NEWLINE;
	else if (!(status & TERM_S_QUOTE) && c == '"')
		status ^= TERM_D_QUOTE;
	else if (!(status & TERM_D_QUOTE) && c == '\'')
		status ^= TERM_S_QUOTE;
	else if (!(status & TERM_B_SLASH) && c == '\\')
		status |= TERM_B_SLASH;
	return (status);
}
