/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:32:31 by dchief            #+#    #+#             */
/*   Updated: 2020/10/28 22:05:51 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash.h"

t_boolean	hash_set(t_hash *root, char *key, char *value)
{
	t_hash *hash;

	hash = hash_get_node(root, key, true);
	return (hash_set_node(hash, key, value));
}

t_boolean	hash_has(t_hash *root, char *key)
{
	t_hash *hash;

	hash = hash_get_node(root, key, false);
	return (hash && hash->value);
}

char		*hash_get(t_hash *root, char *key)
{
	t_hash *hash;

	hash = hash_get_node(root, key, false);
	if (!hash)
		return (NULL);
	return (hash->value);
}

t_boolean	hash_unset(t_hash *root, char *key)
{
	t_hash *hash;

	hash = hash_get_node(root, key, false);
	if (!hash)
		return (false);
	return (hash_unset_node(hash));
}
