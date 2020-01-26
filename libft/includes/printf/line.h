/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 17:07:54 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 18:36:49 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <stddef.h>

typedef struct	s_line
{
	char			*content;
	size_t			size;
	struct s_line	*next;
}				t_line;

t_line			*pf_line_add(t_line **line, char *content, int size);
t_line			*pf_line_clr(t_line **line);
int				pf_line_len(t_line *line);
int				pf_line_put(char **dest, t_line **line, char alloc);

#endif
