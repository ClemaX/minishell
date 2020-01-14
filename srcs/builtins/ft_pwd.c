/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_pwd.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <plamtenz@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/14 06:43:52 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/14 11:12:23 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft.h>
#include <limits.h>
#include <unistd.h>

int		ft_pwd(void)
{
	char cwd[_POSIX_PATH_MAX];

	if (!(getcwd(cwd, sizeof(cwd))))
		return (1);
	ft_printf("%s\n", cwd);
	return (0);
}
