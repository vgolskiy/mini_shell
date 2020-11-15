/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_to_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:40:54 by dchief            #+#    #+#             */
/*   Updated: 2020/10/28 22:13:14 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/common.h"

static char	*hash_get_node_envp(t_hash *node)
{
	if (!node || !node->value)
		return (NULL);
	return (joinstring(node->key, '=', node->value));
}

static void	hash_to_envp_iterator(t_hash *node, t_lst *list)
{
	char	*str;
	int		i;
	int		j;

	if (!node)
		return ;
	str = hash_get_node_envp(node);
	if (str)
		push_to_list(list, str);
	i = 0;
	while (i < 16)
	{
		if (node->next[i])
		{
			j = 0;
			while (j < 16)
			{
				hash_to_envp_iterator(node->next[i][j], list);
				j++;
			}
		}
		i++;
	}
}

char		**hash_to_envp(t_hash *root)
{
	t_lst *list;

	list = init_list();
	hash_to_envp_iterator(root, list);
	return ((char **)to_array(list));
}
