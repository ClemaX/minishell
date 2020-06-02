#include <ft_term.h>
#include <lexer.h>

int	main(int ac, const char **av, const char **envp)
{
	int		ret;
	(void)	ac;
	(void)	av;

    lexer_test();
	ret = term_init(envp);
	if (ret == -1)
		return (ret);
	ret = term_prompt();
	return (ret);
}
