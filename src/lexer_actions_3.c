/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:32:37 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 18:10:18 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/lexer.h"

int			mark_identifier_step_1(t_lexer *p)
{
	int j;

	j = 0;
	while ((p->pos < p->len) && is_valid_in_identifier(p->str[p->pos]))
	{
		if (j == 0 && ft_isdigit(p->str[p->pos]))
			break ;
		lexer_set_next(p, '#');
		j++;
	}
	return (j);
}

int			mark_identifier_step_2(t_lexer *p)
{
	int j;

	j = 0;
	if ((p->pos < p->len) && (p->str[p->pos] >= '0'
				&& p->str[p->pos] <= '9'))
	{
		lexer_set_next(p, '#');
		j++;
	}
	return (j);
}

int			mark_identifier_step_3(t_lexer *p)
{
	int j;

	j = 0;
	if ((p->pos < p->len) && (p->str[p->pos] == '?'))
	{
		lexer_set_next(p, '#');
		j++;
	}
	return (j);
}

void		mark_identifier(t_lexer *p, char x)
{
	int pos1;
	int j;

	pos1 = p->pos;
	if (p->str[p->pos + 1] == '\\')
	{
		lexer_set_next(p, '=');
		return ;
	}
	else
		lexer_set_next(p, x);
	j = mark_identifier_step_1(p);
	if (j == 0)
		j = mark_identifier_step_2(p);
	if (j == 0)
		j = mark_identifier_step_3(p);
	if (j == 0)
	{
		if ((p->state == '\"') || (p->str[p->pos] == '\0') ||
			(p->str[p->pos] == '+') || (p->str[p->pos] == '=') || ft_isspace(p->str[p->pos]))
			p->cat[pos1] = '=';
		else
			p->cat[pos1] = '.';
	}
}
