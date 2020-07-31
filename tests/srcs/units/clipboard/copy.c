#include <tests.h>

int	unit_clip_copy_no_select(void)
{
	static const unsigned	line_len = 0;
	t_term					*t;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	t->select = (t_selection){.start.x=-1U};
	got = clip_copy(t);
	diff = diff_p(".select.start.x=-1U return", got, NULL);
	return (!diff);
}

int	unit_clip_copy_empty(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*expected;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	expected = t->clip.data;
	got = clip_copy(t);
	diff = diff_p("empty selection return", got, expected);
	return (!diff);
}

int	unit_clip_copy_all(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*expected;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	t->select = (t_selection){.start.x=0U, .end.x=line_len};
	expected = t->line->data;
	got = clip_copy(t);
	diff = diff_s("full selection return", got, expected);
	return (!diff);
}

int	unit_clip_copy_part(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*expected;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	t->select = (t_selection){.start.x=0, .end.x=line_len/2};
	if (!(expected = ft_substr(t->line->data, t->select.start.x,
		t->select.end.x - t->select.start.x)))
	{
		perror("Error");
		return (1);
	}
	if (!(got = clip_copy(t)))
	{
		free(expected);
		perror("Error");
		return (1);
	}
	diff = diff_s("partial selection return", got, expected);
	return (!diff);
}

int (*tests_clipboard_copy[])(void) = {
	&unit_clip_copy_no_select,
	&unit_clip_copy_empty,
	&unit_clip_copy_all,
	&unit_clip_copy_part,
	NULL
};
