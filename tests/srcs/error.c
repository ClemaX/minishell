/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   error.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 15:10:19 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 05:26:19 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <libft.h>
#include <stdlib.h>

void	error(void)
{
	ft_printf("Error: %s\n", strerror(errno));
	exit(1);
}
