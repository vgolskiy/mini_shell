/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:24:35 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:10:18 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"

void	hash_set2(t_hash *root, t_pair p1, t_pair p2)
{
	p1.value = ft_strdup(p1.value);
	p2.value = ft_strdup(p2.value);
	assert((p1.value != NULL) && (p2.value != NULL),
			"hash_set2", ": Malloc error", 1);
	hash_set(root, p1.key, p1.value);
	hash_set(root, p2.key, p2.value);
	free(p1.value);
	free(p2.value);
}

void	hash_iterate(t_hash *root, void (fn)(char *key, char *value))
{
	int i;
	int j;

	if (!root)
		return ;
	if (root->key)
		fn(root->key, root->value);
	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			if (root->next[j])
				hash_iterate(root->next[j][i], fn);
			j++;
		}
		i++;
	}
}
