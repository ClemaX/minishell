#include "builtins.h"

int	ft_unset(int ac, const char **av, t_term *t)
{
	// TODO: glob env
	while (ac-- > 1)
	{
		/* if (!key_check(av[ac]))
		{
			ft_printf("%s: %s `%s' : not a valid identifier\n",
				t->name, av[0], av[ac]);
			return (1);
		} */
		t->env = map_del(t->env, av[ac]);
		//glob_env = map_del(cmd->glob_env, cmd->av[cmd->ac]);
	}
	return (0);

}