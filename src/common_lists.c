/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:22:34 by dchief            #+#    #+#             */
/*   Updated: 2020/11/06 17:24:29 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/common.h"

t_lst		*init_list(void)
{
	t_lst *p;

	p = malloc(sizeof(t_lst));
	assert(p != NULL, "init_list", ": Error allocating temporary memory", 1);
	p->count = 0;
	p->first = NULL;
	p->last = NULL;
	return (p);
}

int			push_to_list(t_lst *list, void *value)
{
	t_listelement *el;

	if (!value)
		return (list->count);
	el = malloc(sizeof(t_listelement));
	assert(el != NULL, "push_to_list",
						": Error allocating temporary memory", 1);
	el->value = value;
	el->next = NULL;
	if (!list->last)
	{
		list->last = el;
		list->first = el;
	}
	else
	{
		list->last->next = el;
		list->last = el;
	}
	list->count++;
	return (list->count);
}

int			push_to_list2(t_lst *list, void *v1, void *v2)
{
	push_to_list(list, v1);
	return (push_to_list(list, v2));
}

int			push_to_list3(t_lst *list, void *v1, void *v2, void *v3)
{
	push_to_list(list, v1);
	push_to_list(list, v2);
	return (push_to_list(list, v3));
}

void		**to_array(t_lst *list)
{
	void			**array;
	int				position;
	t_listelement	*el;
	t_listelement	*prev;

	array = malloc((list->count + 1) * sizeof(void *));
	assert(array != NULL, "to_array", ": Error allocating temporary memory", 1);
	position = 0;
	el = list->first;
	free(list);
	while (el)
	{
		array[position] = el->value;
		prev = el;
		el = el->next;
		free(prev);
		position++;
	}
	array[position] = NULL;
	return (array);
}
