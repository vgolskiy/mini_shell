/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_creators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:33:25 by dchief            #+#    #+#             */
/*   Updated: 2020/10/30 13:26:18 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/executor.h"
#include "../include/parser.h"

t_token	*create_argument(t_token *t, int i_start)
{
	int start;
	int stop;
	int temp;

	start = skip_while_category_is(t, ' ', i_start);
	temp = skip_while_category_matches(t, is_special, start);
	(void)temp;
	stop = skip_until_category_matches(t, is_special, start);
	return (create_token(t->context, WORD, start, stop));
}

t_token	*create_word(t_token *t, int i_start)
{
	int mstop;
	int mstart;
	int start;
	int stop;

	mstart = skip_while_category_is(t, ' ', i_start);
	mstop = skip_while_category_matches(t, is_redirection, mstart);
	if (mstop == mstart)
		return (create_argument(t, i_start));
	start = skip_while_category_is(t, ' ', mstop);
	skip_while_category_matches(t, is_special, start);
	stop = skip_until_category_matches(t, is_special, start);
	return (create_token(t->context, IO, mstart, stop));
}

t_token	*create_exec(t_token *p, int i_start)
{
	int start;
	int stop;

	if (p->context->cat[i_start] == '|')
		i_start++;
	start = skip_while_category_is(p, ' ', i_start);
	stop = skip_until_category_is(p, '|', start);
	return (create_token(p->context, EXEC, start, stop));
}

t_token	*create_part(t_token *p, int i_start)
{
	int start;
	int stop;

	if (p->context->cat[i_start] == ';')
		i_start++;
	start = skip_while_category_is(p, ' ', i_start);
	stop = skip_until_category_is(p, ';', start);
	return (create_token(p->context, PART, start, stop));
}
