/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:32:31 by dchief            #+#    #+#             */
/*   Updated: 2020/10/28 17:33:16 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/executor.h"

int	skip_while_category_is(t_token *t, char c, int i)
{
	while ((i < t->stop) && t->context->cat[i] == c)
		i++;
	return (i);
}

int	skip_until_category_is(t_token *t, char c, int i)
{
	while ((i < t->stop) && t->context->cat[i] != c)
		i++;
	return (i);
}

int	skip_while_category_matches(t_token *t, t_boolean matcher(char c), int i)
{
	while ((i < t->stop) && matcher(t->context->cat[i]))
		i++;
	return (i);
}

int	skip_until_category_matches(t_token *t, t_boolean matcher(char c), int i)
{
	while ((i < t->stop) && !matcher(t->context->cat[i]))
		i++;
	return (i);
}
