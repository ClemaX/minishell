#include "lexer.h"

char            **tokenize(char *data)
{
    t_token     *stuff;
    int         nb_of_stuff;

    return (list_to_dptr_char(stuff, nb_of_stuff));
}

char            **list_to_dptr_char(t_token *t, int token_nb)
{
    char        **res;
    t_token     *k;
    int         i;
    int         size;

    if (!(res = malloc(sizeof(char *) * token_nb)))
        return (NULL);
    i = -1;
    while (t)
    {
        k = t;
        size = ft_strlen(k->data);
        if (!(res[++i] = malloc(sizeof(char) * size)))
            return (NULL);
        (void)ft_strlcpy(res[i], k->data, size);
        t = t->next;
        free(k);
    }
    return (res);
}