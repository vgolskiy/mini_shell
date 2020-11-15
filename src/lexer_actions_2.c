/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:08:27 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 17:15:10 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/lexer.h"

void		mark_special(t_lexer *p)
{
	lexer_set_next(p, p->str[p->pos]);
}

t_boolean	should_print_slash(char c)
{
	return (c != '$' && c != '\"' && c != '\\');
}

void		mark_escape(t_lexer *p)
{
	int pos;

	pos = p->pos + 1;
	if (should_print_slash(p->str[pos]) && p->state == '\"')
	{
		lexer_set_next(p, '=');
	}
	else
	{
		lexer_set_next(p, '.');
	}
	lexer_set_next(p, '=');
}

t_boolean	is_valid_in_identifier(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_') || (c == '-'));
}

void		mark_letter(t_lexer *p)
{
	lexer_set_next(p, '=');
}
