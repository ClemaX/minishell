/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   execution.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 03:41:36 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/18 22:15:13 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "parser.h"
#include "unistd.h"

static void		cmd_execution(t_node *node)
{
	if (!node)
		return ;
	if (node->type == "redirect in") /* see t_node_t */
		redirection(node->ch2, node->data, STDIN_FILENO);
	else if (node->type == "redirect off")
		redirection(node->ch2, node->data, STDOUT_FILENO);
	else if (node->type == "cmd_path")
		simple_cmd(node);
}

static void		job_execution(t_node *node)
{
	if (!node)
		return ;
	if (node->type == "our node pipe")
		ft_pipe(node);
	else if (node->type == "our cmd path")
		cmd_execution(node);
}

void			cmd_line_execution(t_node *node)
{
	if (!node)
		return ;
	if (node->type == "out node seq")
	{
		job_execution(node->ch1);
		cmd_line_execution(node->ch2);
	}
	else if (node->type == " background ") // not in subjet
	{
		job_execution(node->ch1);
		cmd_line_execution(node->ch2);
	}
	else
		job_execution(node);
}
