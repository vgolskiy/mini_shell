/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_predicates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:10:39 by dchief            #+#    #+#             */
/*   Updated: 2020/11/06 16:30:06 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_boolean	is_text_cat(char c)
{
	if (c == '.')
		return (true);
	if (c == '=')
		return (true);
	return (false);
}

t_boolean	is_quote(char c)
{
	if (c == '\'')
		return (true);
	if (c == '\"')
		return (true);
	return (false);
}

t_boolean	is_redirection(char c)
{
	if (c == '<')
		return (true);
	if (c == '>')
		return (true);
	return (false);
}

t_boolean	is_special(char c)
{
	if (c == ' ')
		return (true);
	if (c == '>')
		return (true);
	if (c == '<')
		return (true);
	if (c == '|')
		return (true);
	if (c == ';')
		return (true);
	return (false);
}
