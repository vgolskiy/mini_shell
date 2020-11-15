/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_actions_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:04:14 by dchief            #+#    #+#             */
/*   Updated: 2020/11/06 11:35:34 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	enter_state(t_lexer *p)
{
	if ((p->str[p->pos] == p->str[p->pos + 1]) &&
		(((p->pos > 0) && (p->str[p->pos - 1] == ' ')) ||
			(p->str[p->pos + 2] == ' ')))
	{
		lexer_set_next(p, '!');
		lexer_set_next(p, '!');
	}
	else
	{
		p->state = p->str[p->pos];
		lexer_set_next(p, '.');
	}
}

void	leave_state(t_lexer *p)
{
	lexer_set_next(p, '.');
	p->state = '\0';
}
