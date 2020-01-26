/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:41:33 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/26 21:50:45 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <prompt.h>
#include <line.h>
#include <libft.h>

static void     move_in_words(t_term *term, int *pos, int(*x)(char *, int *))
{
    char    *line;
    int     bkp;
    
    bkp = *pos;
    line = line_cat(term->line->line, 0);
    tputs(tgoto(term->caps.ch, 0, x(line, pos)), 1, &ft_putchar);
}

void            manage_shortcuts(t_term *term, char signal)
{
    if (signal == COPY) /* ctrl+s */
        handle_cpy_and_cut(term, signal, term->cursor.x, ft_copy);
    else if (signal == CUT) /* ctrl+x */
        handle_cpy_and_cut(term, signal, term->cursor.x, ft_cut);
    else if (signal == PASTE) /* ctrl+w */
        ft_paste(&term->line->line, term->cursor.x, term->copy);
    else if (signal == "ctrl right") /* unknown */
        move_in_words(term, &term->cursor.x, next_wd_right);
    else if (signal == "ctrl left") /* a fcking mistery */
        move_in_words(term, &term->cursor.x, next_wd_left);
    else if (signal == "home") /* 27 and read of 2 -> buff[1] = 72*/
        tputs(tgoto(term->caps.ch, 0, 9), 1, &ft_putchar);
    else if (signal == "end")  /* 27 and read of 2 buff[1] = 70 */
        tputs(tgoto(term->caps.ch, 0, term->cursor.max.x), 1, &ft_putchar);
}

/* home and end must be add to other {27, 91, * }  */