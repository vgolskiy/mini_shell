/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 13:58:49 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

char		*temp_string(int size)
{
	char *tmp;

	tmp = malloc(size);
	assert(tmp != NULL, "temp_string", ": Malloc error", 1);
	ft_memset(tmp, '\0', size);
	return (tmp);
}

char		*concat_string_filtering_empty(t_lst *list)
{
	char *arg;

	arg = concat_string(list, true);
	if (ft_strlen(arg))
		return (arg);
	free(arg);
	return (NULL);
}

t_boolean	has_child(t_hash *node, char letter)
{
	unsigned char low;
	unsigned char high;

	low = letter % 16;
	high = letter / 16;
	if (!node)
		return (false);
	if (!node->next[low])
		return (false);
	return (!!node->next[low][high]);
}

char		*get_next_space(char *c)
{
	while (*c && !ft_isspace(*c))
		c++;
	if (*c)
		return (c);
	return (NULL);
}
