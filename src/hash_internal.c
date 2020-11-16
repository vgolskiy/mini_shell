/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:44:00 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 13:59:24 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"

static t_boolean	hash_null_node(t_hash *node)
{
	if (!node->key)
		return (false);
	if (node->value)
		free(node->value);
	free(node->key);
	node->key = NULL;
	node->value = NULL;
	return (true);
}

void				hash_destroy(t_hash *root)
{
	int i;
	int j;

	if (!root)
		return ;
	hash_null_node(root);
	i = 0;
	while (i < 16)
	{
		if (root->next[i])
		{
			j = 0;
			while (j < 16)
			{
				hash_destroy(root->next[i][j]);
				j++;
			}
			free(root->next[i]);
		}
		i++;
	}
	free(root);
}

t_boolean			hash_set_node(t_hash *hash, char *key, char *value)
{
	t_boolean code;

	code = hash_null_node(hash);
	if (value)
		hash->value = ft_strdup(value);
	hash->key = ft_strdup(key);
	assert((hash->key != NULL) && (!value || (hash->value != NULL)),
			"hash_set_node", ": Malloc error", 1);
	return (code);
}

t_boolean			hash_unset_node(t_hash *node)
{
	t_boolean code;

	code = hash_null_node(node);
	hash_cleanup(node);
	return (code);
}

t_hash				*hash_get_node(t_hash *root, char *key, t_boolean force)
{
	t_hash			*hash;
	unsigned char	letter;
	unsigned char	low;
	unsigned char	high;

	hash = root;
	while ((letter = *(key++)) && hash)
	{
		low = letter % 16;
		high = letter / 16;
		if (hash->next[low] && hash->next[low][high])
		{
			hash = hash->next[low][high];
		}
		else if (force)
		{
			hash = hash_create_child(hash, letter);
		}
		else
		{
			hash = NULL;
		}
	}
	return (hash);
}
