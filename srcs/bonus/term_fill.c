/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:56:34 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/26 21:17:29 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <line.h>
#include <prompt.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft.h>

void            ft_paste(t_term *term, int pos, char *to_paste)
{
    if (to_paste)
    {
        line_insert_at(term->line->line, pos, to_paste);
        term->cursor.max.x += ft_strlen(to_paste);
    }
}

char             *ft_copy(t_term *term, int pos, int dir, int size)
{
    char    *copy;

    if (size <= 0)
        return (NULL);
    if (dir < 0)
        copy = line_get_range(term->line->line, pos - size, pos);
    else
        copy = line_get_range(term->line->line, pos, size);
    return (copy);
}

char            *ft_cut(t_term *term, int pos, int dir, int size)
{
    char    *copy;

    if (size <= 0)
        return (NULL);
    if (dir < 0)
    {
        copy = line_get_range(term->line->line, pos - size, pos);
        term->line->line = del_line(term->line->line, pos - size, pos);
    }
    else if (dir > 0)
    {
        copy = line_get_range(term->line->line, pos, size);
        term->line->line = del_line(term->line->line, pos, size);
    }
    term->cursor.max.x -= size;
    return (copy);
}

static void     handle_cpy_and_cut_arrows(int *size, int *dir)
{
    char    buff[2];
    int     ret;

    while ((ret = read(STDIN_FILENO, buff, 2)) == 1
            && (buff[1] == 'D' || buff[1] == 'C' || c == ENTER))
    {
        if (c == ENTER)
            break ;
        else if (buff[1] == 'D')
            *size++;
        else if (buff[1] == 'C')
            *size--;
    }
    if (size < 0)
    {
        *size = -*size;
        *dir = -1;
    }
}

void            handle_cpy_and_cut(t_term *term, char signal, int pos, char *(*x)(t_term *, int, int, int))
{
    int     ret;
    int     dir;
    int     size;
    char    c;

    dir = 1;
    size = 0;
    while ((ret = read(STDIN_FILENO, &c, 1)) == 1
        && (c == ENTER || ft_isdigit(c) || c == MINUS))
    {
        if (c == ENTER)
            break ;
        if (!size && c == MINUS)
            dir = -dir;
        if (ft_isdigit(c))
            size = size * 10 + (int)c;
    }
    if (!size && c == '\e')
        handle_cpy_and_cut_arrows(&size, &dir);
    term->copy = x(term, pos, dir, size);
}
