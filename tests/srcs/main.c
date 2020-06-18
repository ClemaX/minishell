/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:47:17 by chamada           #+#    #+#             */
/*   Updated: 2020/06/15 22:40:51 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int			main(void)
{
	int	err;

	err = 0;
	err |= !run_tests("clipboard", tests_clipboard, 3);
	return (err);
}
