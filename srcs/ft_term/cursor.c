#include <ft_term.h>

void    term_up(void)
{
    tputs(g_term.caps.c_up, 0, &ft_putchar);
}

void    term_down(void)
{
    tputs(g_term.caps.c_down, 0, &ft_putchar);
}

void    term_left(void)
{
    tputs(g_term.caps.c_left, 0, &ft_putchar);
}

void    term_right(void)
{
    tputs(g_term.caps.c_right, 0, &ft_putchar);
}
