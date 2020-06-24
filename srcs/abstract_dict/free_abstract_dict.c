#include <abstract_dict.h>

void        *free_abstract_dict(t_op *ad)
{
    t_op    *aux;

    if (!ad)
        return (NULL);
    if (ad->type & PARENTHESIS)
        free_abstract_dict(ad->ch1);
    if (ad->ch1)
        free(ad->ch1);
    if (ad->ch2)
        free(ad->ch2);
    aux = ad;
    ad = ad->next;
    free(aux);
    return (free_abstract_dict(ad));
}