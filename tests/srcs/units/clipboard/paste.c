/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 15:58:33 by chamada           #+#    #+#             */
/*   Updated: 2020/08/23 15:58:33 by chamada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tests.h>

int	unit_clip_paste_no_clip(void)
{
	static const unsigned	line_len = 10;
	t_term					*t;
	char					*got;
	char					*expected;
	int						diff;

	t = rand_term(line_len);
	if (!(expected = ft_strdup(t->line->data)))
	{
		perror("Error");
		return (1);
	}
	t->clip.data = NULL;
	t->clip.length = 0;
	t->clip.size = 0;
	clip_paste(t);
	got = t->line->data;
	diff = diff_s("empty clipboard return", got, expected);
	free(expected);
	return (!diff);
}

int	unit_clip_paste_empty(void)
{
	static const unsigned	clip_len = 10;
	t_term					*t;
	char					*got;
	char					*expected;
	int						diff;

	t = rand_term(0);
	if (!(t->clip.data = rand_key(clip_len))
	|| !(expected = ft_strdup(t->clip.data)))
	{
		perror("Error");
		return (1);
	}
	t->clip.length = clip_len;
	t->clip.size = clip_len + 1;
	clip_paste(t);
	got = t->line->data;
	diff = diff_s("empty line return", got, expected);
	free(expected);
	return (!diff);
}

int	unit_clip_paste_insert(void)
{
	static const unsigned	len = 10;
	const unsigned			pos = ft_rand(1, len);
	t_term					*t;
	char					*expected;
	int						diff;

	t = rand_term(len);
	t->cursor.pos.x = pos;
	if (!(t->clip.data = rand_key(len))
	|| !(expected = malloc(sizeof(*expected) * len * 2)))
	{
		perror("Error");
		return (1);
	}
	t->clip.length = len;
	t->clip.size = len + 1;
	ft_memcpy(expected, t->line->data, t->cursor.pos.x);
	ft_memcpy(expected + t->cursor.pos.x, t->clip.data, t->clip.length);
	ft_memcpy(expected + t->cursor.pos.x + t->clip.length,
		t->line->data + t->cursor.pos.x, t->cursor.pos.x);
	expected[len * 2] = '\0';
	clip_paste(t);
	diff = diff_s("random insert return", t->line->data, expected);
	free(expected);
	return (!diff);
}

int	(*g_tests_clipboard_paste[])(void) = {
	&unit_clip_paste_no_clip,
	&unit_clip_paste_empty,
	&unit_clip_paste_insert,
	NULL
};
