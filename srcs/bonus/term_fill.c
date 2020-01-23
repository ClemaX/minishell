/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:56:34 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/23 16:31:24 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void key_sign_to_int(int *selected, char signal)
{
    *selected = *selected * 10 + (int)signal;
}

int         ft_copy(int status, int *selected, char siganl, t_list *imput_list, int pos, int *len)
{
    if (!selected && len) /* with arrows */
    {
        if (len > 0)
            get_range(imput_list, pos, *len);
        else if (len < 0)
            get_range(imput_list, pos - *len, pos);
    }
    else if (!(status & 2))
        get_range(imput_list, pos, selected);       /* this must return a str i should use it (put it on a struct could be a good idea) */

    else if (status & 2)
        get_range(imput_list, pos - *selected, pos);
    *selected = 0;
    *len = 0;
    return (0);
}

int         ft_cut(int status, int *selected, char siganl, t_list *imput_list, int pos, int *len)
{
    if (!selected && len) /* with arrows */
    {
        if (len > 0)
        {
            get_range(imput_list, pos, *len);
            delete_range(imput_list, pos, *len)
        }
        else if (len < 0)
        {
            get_range(imput_list, pos - *len, pos);
            delete_range(imput_list, pos - *len, pos);
        }
    }
    else if (!(status & 2))
    {
        get_range(imput_list, pos, *selected);       /* this must return a str i should use it (put it on a struct could be a good idea) */
        delete_range(imput_list, pos, *selected)
    }

    else if (status & 2)
    {
        get_range(imput_list, pos - *selected, pos);
        delete_range(imput_list, pos - *selected, pos);
    }
    *selected = 0;
    *len = 0;
    return (0);
}


/*

status -> bit[0] = cpy process
status -> bit[1] = inverse copy

*/
    
int         copy_cut_call(char signal, int *status, t_list *imput_list, int pos, int(*f)(int, int *, char, t_list *, int , int *)) /* call this fck each time a key is pressed */
{
    static int  selected;
    static int len;

    if (*status & 1 && signal != "digit key" && signal != "minus key" && signal != "left arrow" && signal != "right arrow")
        ft_copy(status, selected, imput_list, pos, len);
    if (signal == "copy signal" || (*status & 1 && !(signal == "digit keys" && signal == "minus key"
            && signal != "left arrow" && status != "right arrow"))) /* probally have to add a end key */
        *status ^= (1 << 0);
    if (*status & 1 && (signal == "digit keys" || signal == "minus key" || signal == "right arrow" && signal == "left arrow"))
    {
        if (status == "right arrow")
            len++;
        if (status == "left arrow")
            len--;
        *status |= signal == "minus signal" && !(*status & 2) && !selected ? 2 : 0;
        if (signal == "digit keys")
            key_sign_to_int(&selected, signal);
    }
    return (0);
}

int         ft_paste(int pos, char signal, char *to_paste)
{
    if (signal == "paste code")
        insert_arg(pos, to_paste);
    return (0);
}

