/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:47:17 by chamada           #+#    #+#             */
/*   Updated: 2020/08/18 15:39:56 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int			main(void)
{
	int	err;

	err = 0;
	err |= !run_tests("cut", tests_clipboard_cut, 3);
	err |= !run_tests("copy", tests_clipboard_copy, 3);
//	err |= !run_tests("paste", tests_clipboard_paste, 3);
	return (err);
}
