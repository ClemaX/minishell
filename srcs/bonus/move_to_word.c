/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:22:26 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/23 18:48:19 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

/* 2 pointer to fct called when we do ctrl+right or ctrl+left */

int         next_wd_right(char *line, int *pos)
{
    int     cont;

    cont = 0;
    if (*line &&ft_isspace(*line))
    {
        while (*line && ft_isspace(*line++))
            cont++;
    }
    else
    {
        while (*line && !ft_isspace(*line++))
            cont++;
        while (*line && ft_isspace(*line++))
            cont++;
    }
    *pos += cont + 1;
    return (*pos);
}

int         next_wd_left(char *line, int *pos)
{
    int     cont;
    int     i;

    cont = 0;
    i = *pos;
    if (i >= 0 && !ft_isspace(line[i]))
    {
        while (i >= 0 && !ft_isspace(line[i--]))
            cont++;
    }
    else
    {
        while (i >= 0 && ft_isspace(line[i--]))
            cont++;
        while (i >= 0 && !ft_isspace(line[i]--))
            cont++;
    }
    *pos -= cont + 1;
    return (*pos);
}