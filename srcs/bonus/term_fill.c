/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:56:34 by plamtenz          #+#    #+#             */
/*   Updated: 2020/01/23 14:46:43 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
gonna implement 2 ways to copy:
    - The first one is a signal keys + a number: this ll cy the number of char sipefied if is possible
    - The second one is to use a signal key and select what ll be copy with the arrows RIGHT AND LETF and stop with a signal
*/ 

static void key_sign_to_int(int *selected, char signal)
{
    *selected = *selected * 10 + (int)signal; /* if that doesn t work try atoi method */
}

int         ft_copy(int status, int *selected, char siganl, t_list *imput_list)
{
    int  it;
    char buff[1024]; /* have to do something with that */

    if (!selected)
    {
        /* this shit is hard have to think or use static var 
        
        must select test with arrows, i can also deselect test (this second one fcks up all)
        
        */
    }
    else if (status & 2); /* dirrection > 0 meas we copy left to right */
    {
        it = 0;
        while (it < *selected && imput_list)
        {
            buff[it++] = imput_list->data;
            imput_list = imput_list->next;
        }
    }
    else
    {
        it = *selected;
        while (*selected-- && imput_list) /* going back in a lst can i check if i could overflow ? */
        {
            buff[*selected] = imput_list->data;
            imput_list = imput_list->back;
        }
    }
    *selected = 0;
    return (0);
}


/*

status -> bit[0] = cpy process
status -> bit[1] = inverse copy

*/
status = 0;
copy_call(signal, &status, imput_lst);
    
int         copy_call(char signal, int *status, t_list *imput_list) /* call this fck each time a key is pressed */
{
    static int  selected;

    if (*status & 1 && signal != "digit key" && signal != "minus key")
        ft_copy(status, selected, imput_list);
    if (signal == "copy signal" || (*status & 1 && !(signal == "digit keys" && signal == "minus key")))
        *status ^= (1 << 0);
    if (*status & 1 && (signal == "digit keys" || signal == "minus key"))
    {
        *status |= signal == "minus signal" && !(*status & 2) && !selected ? 2 : 0;
        if (signal == "digit keys")
            key_sign_to_int(&selected, signal); /* selected  * 10 + signal in int */
    }
    return (0);
}

/* cut is exactly the same as copy but txt will be deletd in term and first selected - 1 and last + 1 will be concat:
    -just need a function who does that in the term, we must implement first the option to remove text to the term

    for paste is only same as the option to write where the cursor is located need to implemet that before continue with this fcnts

*/

