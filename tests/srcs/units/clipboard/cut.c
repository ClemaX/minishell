#include <tests.h>

int	unit_clip_cut_no_select(void)
{
	static const unsigned	line_len = 0;
	t_term					*t;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	t->select = (t_selection){.start.x=-1U};
	got = clip_cut(t);
	diff = diff_p(".select.start.x=-1U return", got, NULL);
	return (!diff);
}

int	unit_clip_cut_empty(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*expected;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	expected = t->clip.data;
	got = clip_cut(t);
	diff = diff_p("empty selection return", got, expected);
	return (!diff);
}

int	unit_clip_cut_all(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*expected;
	char					*got;
	int						diff;

	t = rand_term(line_len);
	t->select = (t_selection){.start.x=0U, .end.x=line_len};
	if (!(expected = ft_strdup(t->line->data)))
	{
		perror("Error");
		return (1);
	}
	if (!(got = clip_cut(t)))
	{
		free(expected);
		perror("Error");
		return (1);
	}
	diff = diff_s("full selection return", got, expected);
	return (!diff);
}

int	unit_clip_cut_part(void)
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
	if (!(got = clip_cut(t)))
	{
		free(expected);
		perror("Error");
		return (1);
	}
	diff = diff_s("partial selection return", got, expected);
	return (!diff);
}

int (*tests_clipboard_cut[])(void) = {
	&unit_clip_cut_no_select,
	&unit_clip_cut_empty,
	&unit_clip_cut_all,
	&unit_clip_cut_part,
	NULL
};
