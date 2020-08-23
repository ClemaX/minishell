/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:47:17 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 16:07:47 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int	main(void)
{
	int	err;
	int	fd[2];

	fd[0] = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	fd[1] = open("err.log", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd[0] < 0 || fd[1] < 0)
	{
		perror("Could not open logfiles");
		return (1);
	}
	err = 0;
	err |= !run_tests(fd, "cut", g_tests_clipboard_cut, 3);
	err |= !run_tests(fd, "copy", g_tests_clipboard_copy, 3);
	err |= !run_tests(fd, "paste", g_tests_clipboard_paste, 3);
	close(fd[0]);
	close(fd[1]);
	return (err);
}
