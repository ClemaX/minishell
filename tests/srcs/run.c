/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 16:34:23 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 15:53:03 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

static int	handle_crash(int st)
{
	if (WIFSIGNALED(st))
	{
		if ((st = WTERMSIG(st)) == SIGSEGV)
			printf(C_SEGV);
		else if (st == SIGABRT)
			printf(C_ABRT);
		else
			printf("%d", st);
	}
	else
		printf(C_NONE);
	return (1);
}

static int	handle_result(pid_t child_pid)
{
	int	st;

	while (waitpid(child_pid, &st, 0) < 0)
		;
	if (WIFEXITED(st))
	{
		st = WEXITSTATUS(st);
		dprintf(1, st ? FAIL : PASS);
		return (st);
	}
	else
		return (handle_crash(st));
}

static int	run_test(int *fd, int (*test)(void), int iterations)
{
	int		i;
	pid_t	pid;
	int		err;

	i = 0;
	err = 0;
	while (i++ < iterations)
	{
		if (!(pid = fork()))
		{
			dup2(fd[0], 1);
			dup2(fd[1], 2);
			exit(!(*test)());
		}
		else if (pid < 0)
		{
			perror("Fatal error: Could not fork");
			exit(1);
		}
		err += handle_result(pid);
	}
	return (err);
}

int			run_tests(int *fd, char *label, int (*tests[])(void),
	int iterations)
{
	int err;
	int i;

	dprintf(1, "%s %*s\t",
		BULLET, LBL_FW, label);
	i = 0;
	err = 0;
	while (tests[i])
	{
		err += run_test(fd, tests[i], iterations);
		i++;
		if (tests[i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (!err);
}
