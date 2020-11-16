/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:57:20 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:01:05 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"

static t_hash	**new_block(void)
{
	t_hash	**p;
	int		i;

	p = malloc(16 * sizeof(t_hash *));
	assert(p != NULL, "new_block", "Malloc error", 1);
	i = 0;
	while (i < 16)
		p[i++] = NULL;
	return (p);
}

t_boolean		hash_is_empty_node(t_hash *p)
{
	int i;

	i = 0;
	if (p->key)
		return (false);
	if (p->value)
		return (false);
	while (i < 16)
	{
		if (p->next[i++])
			return (false);
	}
	return (true);
}

t_hash			*hash_create_child(t_hash *parent, char letter)
{
	t_hash			*node;
	unsigned char	low;
	unsigned char	high;

	node = hash_create_node();
	if (!node)
		return (NULL);
	node->letter = letter;
	node->parent = parent;
	low = letter % 16;
	high = letter / 16;
	if (!parent->next[low])
		parent->next[low] = new_block();
	return (parent->next[low][high] = node);
}

t_hash			*hash_create_node(void)
{
	t_hash	*hash;
	int		i;

	i = 0;
	hash = malloc(sizeof(t_hash));
	assert(hash != NULL, "hash_create_node", "Malloc error", 1);
	hash->letter = '\0';
	hash->parent = NULL;
	hash->value = NULL;
	hash->key = NULL;
	while (i < 16)
		hash->next[i++] = NULL;
	return (hash);
}

void			hash_cleanup(t_hash *p)
{
	unsigned char	low;
	unsigned char	high;
	int				i;
	t_hash			*parent;
	t_hash			**block;

	while (hash_is_empty_node(p))
	{
		low = p->letter % 16;
		high = p->letter / 16;
		parent = p->parent;
		free(parent->next[low][high]);
		parent->next[low][high] = NULL;
		block = parent->next[low];
		i = 0;
		while (i < 16)
		{
			if (block[i++])
				return ;
		}
		free(parent->next[low]);
		parent->next[low] = NULL;
		p = parent;
	}
}
