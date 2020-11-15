/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:06 by dchief            #+#    #+#             */
/*   Updated: 2020/10/28 22:29:06 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "./common.h"
# include "../libft/libft.h"

typedef struct			s_hash_node
{
	struct s_hash_node	**next[16];
	struct s_hash_node	*parent;
	char				letter;
	char				*key;
	char				*value;
}						t_hash;

typedef struct
{
	char*				key;
	char*				value;
}						t_pair;

t_hash					*hash_create_node(void);
t_hash					*hash_create_child(t_hash *parent, char letter);

t_hash					*hash_get_node(t_hash *root,
						char *key, t_boolean force);
t_boolean				hash_is_empty_node(t_hash *hash);
t_boolean				hash_unset_node(t_hash *node);
void					hash_cleanup(t_hash *hash);

char					*hash_get(t_hash *root, char *key);
t_boolean				hash_set(t_hash *root, char *key, char *value);
t_boolean				hash_unset(t_hash *root, char *key);
t_boolean				hash_has(t_hash *root, char *key);
void					hash_destroy(t_hash *root);
void					hash_iterate(t_hash *root,
						void(fn)(char *key, char *value));

void					hash_set2(t_hash *root, t_pair p1, t_pair p2);
t_boolean				hash_set_node(t_hash *hash, char *key, char *value);

#endif
