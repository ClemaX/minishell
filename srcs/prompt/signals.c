/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   signals.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 12:11:46 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/27 21:08:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <signal.h>
#include <global_var.h>
#include <libft.h>
#include <prompt.h>
#include <line.h>

void	sig_handler(int sig, void *param)
{
	static t_term	*term;

	if (!term)
		term = param;
	else
	{
		if (sig == SIGINT)
		{
			if (g_pid)
			{
				kill(g_pid, sig);
				g_pid = 0;
			}
			ft_printf("\nminish>$ ");
			term->cursor = (t_cursor){.x=0, .y=0};
			line_clr(&term->line);
			return ;
		}
		else if (g_pid && sig == SIGQUIT)
		{
			kill(g_pid, sig);
			ft_printf("quit: %d\n", g_pid);
			g_pid = 0;
			return ;
		}
	}
}

void	sig_init(t_term *term)
{
	sig_handler(0, term);
	signal(SIGINT, (void (*)(int))&sig_handler);
	signal(SIGQUIT, (void (*)(int))&sig_handler);
}
