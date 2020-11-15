/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:24:00 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 20:24:38 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static void	tokenize(t_lexer *p)
{
	char s;
	char l;

	s = p->state;
	l = p->str[p->pos];
	if (s == l)
		return (leave_state(p));
	if (s == '\0' && l == '$')
		return (mark_identifier(p, '@'));
	if (s == '\"' && l == '$')
		return (mark_identifier(p, '$'));
	if (s != '\'' && l == '\\')
		return (mark_escape(p));
	if (s == '\0' && is_quote(l))
		return (enter_state(p));
	if (s == '\0' && is_special(l))
		return (mark_special(p));
	return (mark_letter(p));
}

void		lexer_set_next(t_lexer *p, char cat)
{
	p->cat[p->pos] = cat;
	p->stt[p->pos] = p->state == '\0' ? ' ' : p->state;
	p->pos++;
}

t_lexer		*init_parser(char *input)
{
	t_lexer *p;

	p = malloc(sizeof(t_lexer));
	assert(p != NULL, "hash_set_node",
		": Error allocating temporary memory", 1);
	p->str = input;
	p->cat = ft_strdup(input);
	p->stt = ft_strdup(input);
	assert(p->cat != NULL, "hash_set_node",
		": Error allocating temporary memory", 1);
	assert(p->stt != NULL, "hash_set_node",
		": Error allocating temporary memory", 1);
	p->len = (int)ft_strlen(input);
	ft_memset(p->stt, '_', p->len);
	p->stt[0] = ' ';
	p->pos = 0;
	p->state = '\0';
	while (p->pos < p->len)
		tokenize(p);
	return (p);
}

void		lexer_destroy(t_lexer *my)
{
	if (my->cat)
		free(my->cat);
	my->cat = NULL;
	if (my->stt)
		free(my->stt);
	my->stt = NULL;
	if (my->str)
		free(my->str);
	my->str = NULL;
	free(my);
}
