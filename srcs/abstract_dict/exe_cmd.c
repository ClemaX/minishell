#include "abstract_dict.h"
#include <limits.h>

static

char		*path_cat(const char *a, const char *b)
{
	const size_t	len = ft_strlen(a) + ft_strlen(b) + 1;
	char			*cat;
	char			*c;

	if (len > PATH_MAX || !(cat = ft_calloc(len + 1, sizeof(*cat))))
		return (NULL);
	c = cat;
	while (*a)
		*c++ = *a++;
	*c++ = '/';
	while (*b)
		*c++ = *b++;
	return (cat);
}

char		*path_get(const char *name, const char *path)
{
	char		**paths;
	char		*join;
	struct stat	s;
	int			i;

	if (!name || !*name || !(paths = ft_split(path, ':')))
		return (NULL);
	i = 0;
	while (paths[i])
	{
		if (!(join = path_cat(paths[i++], name)))
			return (strs_unload(paths));
		if (stat(join, &s) == 0 && s.st_mode & S_IXUSR)
		{
			strs_unload(paths);
			return (join);
		}
		free(join);
	}
	strs_unload(paths);
	return (NULL);
}

int         builting_not_in_slash_bin(int ac, char** argv, t_term *t)
{
    const char *name = argv[0];

    if (!ft_strncmp(name, "echo", 5))
        return (ft_echo(ac, argv)); // false is true
    else if (!ft_strncmp(name, "cd", 3))
        return (ft_cd(ac, argv, t));
    else if (!ft_strncmp(name, "pwd", 4))
        return (ft_pwd());
    else if (!ft_strncmp(name, "export", 7))
        return (ft_export(ac, argv, t));
    else if (!ft_strncmp(name, "unset", 6))
        return (ft_unset(ac, argv, t));
    else if (!ft_strncmp(name, "env", 4))
        return (ft_env(t->env));
    else if (!ft_strncmp(name, "exit", 5))
        return (ft_exit());
    return (true);
}

int         execute_cmd(t_token *data, t_term *t)
{
	ft_dprintf(2, "[data %p]\n", data);
	ft_dprintf(2, "exe cmd\n");
	char	**envp;
    char	**argv;
	char	*path;
	int		ac;

    if (!(argv = token_tab(data, &ac)))
        return (-1);
    if ((t->st = builting_not_in_slash_bin(ac, argv, t)))
    {
		if (!(envp = map_export(t->env)))
		{
			ft_dprintf(2, "could not export environment!");
			free((char**)argv);
			return (false);
		}
		if (!(path = path_get(argv[0], map_get(t->env, "PATH")->value)))
		{
			ft_dprintf(2, "path not found! name is [%s]\n", argv[0]);
			ft_printf("%s: %s: command not found\n", t->name, argv[0]);
			free((char**)argv);
			free(envp);
			return (BASH_ERROR_CODE);
		}
		if (!(t->pid = fork()))
		{

        	t->st = execve(path, argv, envp);
        	ft_dprintf(2, "execve returned! name is [%s] [%d]\n", argv[0], t->st); // name or errno ?
			return (BASH_ERROR_CODE);
		}
    	else if (t->pid < 0)
        	return (BASH_ERROR_CODE);
    	while (waitpid(t->pid, NULL, 0) < 0)
        	;
		// Free allocated variables
		free(envp);
		free(path);
    	t->pid = 0;
	}
	free((char**)argv);
    return (true);
}

int         execute_and(t_op *ad, t_term *t)
{
    if (ad->ch1 == NULL && t->st)
        return (false);
    if (ad->ch1 && ad->ch2)
    {
        (void)execute_cmd(ad->ch1, t);
        if (t->st)
            return (false);
        (void)execute_cmd(ad->ch2, t);
    }
	else if (ad->ch1)
		(void)execute_cmd(ad->ch1, t);
    return (true);
}

int         execute_or(t_op *ad, t_term *t)
{
    if (ad->ch1 == NULL && !t->st)
        return (false);
    if (ad->ch1 && ad->ch2)
    {
		if (!t->st)
            return (false);
        (void)execute_cmd(ad->ch1, t);
        if (!t->st)
            return (false);
        (void)execute_cmd(ad->ch2, t);
    }
	else if (ad->ch1 && t->st)
		(void)execute_cmd(ad->ch1, t);
    return (true);
}
