#include <ft_term.h>
#include <lexer.h>

int exec(const char *str)
{
    ft_printf("Input: %s", str);
    return (0);
}

int	main(int ac, const char **av, const char **envp)
{
	int		    ret;
	(void)	    ac;
	(void)	    av;

	ret = term_init(envp);
	if (ret == -1)
		return (ret);
	ret = term_prompt(&exec);
	return (ret);
}
