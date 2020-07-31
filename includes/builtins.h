#ifndef BUILTINS_H
# define BUILTINS_H

#include <libft.h>
#include "ft_term.h"
#include <linux/limits.h>
#include <unistd.h>
#include <stdlib.h>

int		ft_cd(int ac, const char **argv, t_term *t);
int	    ft_echo(int ac, const char **argv);
int	    ft_env(t_map *env);
int		ft_exit(void);
int	    ft_export(int ac, const char **av, t_term *t);
int		ft_pwd(void);
int	    ft_unset(int ac, const char **av, t_term *t);

#endif