#include <tests.h>

int	unit_clip_copy_no_select(void)
{
	t_term				*t;
	char				*got;
	int					diff;

	t = rand_term(0);
	t->select = (t_selection){.start.x=-1U};
	got = clip_copy(t);
	diff = diff_p(".select.start.x=-1U return", got, NULL);
	return (!diff);
}

int	unit_clip_copy_empty(void)
{
	t_term				*t;
	char				*got;
	int					diff;

	t = rand_term(10);
	got = clip_copy(t);
	diff = diff_p(".select.start.x=-1U return", got, NULL);
	return (!diff);
}

int (*tests_clipboard[])(void) = {
	&unit_clip_copy_no_select,
	&unit_clip_copy_empty,
	NULL
};
