#include "builtins.h"

int	ft_unset(t_term *t, char *name)
{
	while (cmd->ac-- > 1) // to do 
	{
		if (!key_check(cmd->av[cmd->ac]))
		{
			ft_printf("%s: %s `%s' : not a valid identifier\n",
				name, cmd->av[0], cmd->av[cmd->ac]);
			return (1);
		}
		cmd->env = map_del(cmd->env, cmd->av[cmd->ac]);
		cmd->glob_env = map_del(cmd->glob_env, cmd->av[cmd->ac]);
	}
	return (0);

}