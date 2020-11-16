/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:22:34 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 13:58:49 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/common.h"
#include "../include/parser.h"

static int	get_total_length(char **parts)
{
	int length;

	length = 0;
	while (*parts)
	{
		length += ft_strlen(*parts);
		parts++;
	}
	return (length);
}

static void	concat_string_core(char *target, char **parts, t_boolean autofree)
{
	char *source;
	char **current;

	current = parts;
	while (*current)
	{
		source = *current;
		while (*source)
			*(target++) = *(source++);
		if (autofree)
			free(*current);
		current++;
	}
	free(parts);
	*target = '\0';
}

char		*concat_string(t_lst *list, t_boolean autofree)
{
	char **parts;
	char *str;

	parts = (char **)to_array(list);
	str = malloc(get_total_length(parts) + 1);
	assert(str != NULL, "concat_string", ": Malloc error", 1);
	concat_string_core(str, parts, autofree);
	return (str);
}

char		*joinstring(char *a, char sep, char *b)
{
	int		l;
	char	*str;
	char	*c;

	l = (int)ft_strlen(a) + 1 + (int)ft_strlen(b);
	str = malloc(l + 1);
	assert(str != NULL, "joinstring", ": Malloc error", 1);
	c = str;
	while (*a)
		*(c++) = *(a++);
	if (sep)
		*(c++) = sep;
	while (*b)
		*(c++) = *(b++);
	str[l] = '\0';
	return (str);
}

char		*safe_clone(char *start, char *stop)
{
	char *tmp;

	if (stop == NULL)
	{
		stop = start;
		while (*stop)
			stop++;
	}
	tmp = temp_string(stop - start + 1);
	ft_memcpy(tmp, start, stop - start + 1);
	tmp[stop - start] = 0;
	return (tmp);
}
