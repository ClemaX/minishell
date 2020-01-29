/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   line.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/20 17:07:54 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 03:33:17 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

# include <stddef.h>

typedef struct	s_line
{
	char			c;
	struct s_line	*next;
}				t_line;

t_line			*line_add(t_line **line, char c);
t_line			*line_clr(t_line **line);
int				line_len(t_line *line);
int				line_put(char **dest, t_line **line, char clr);
char			*line_get(t_line **line);
char			*line_cat(t_line **line, char clr);
void			line_insert_at(t_line **line, int pos, char *str);
void			line_insert_at_c(t_line **line, int pos, char c);
char			*line_get_range(t_line *line, int min, int max);
t_line			*line_dup(t_line *line);
t_line			*line_del_range(t_line *line, int min, int max, int i);

#endif
