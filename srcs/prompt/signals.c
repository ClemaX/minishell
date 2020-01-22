/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 12:11:46 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/22 14:01:19 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <signal.h>
#include <global_var.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_printf("\nminish>$ ");
	else if (sig == SIGQUIT)
	{
		ft_printf("TODO: quit\nminish>$ ");
}

void	sig_init(void)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
}
