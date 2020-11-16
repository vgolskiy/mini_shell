/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:24:34 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 13:58:49 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/common.h"
#include "../include/executor.h"

void		stringlist_destroy(char **list)
{
	char **c;

	c = list;
	while (*c)
		free(*(c++));
	free(list);
}

int			hash_verify_key(char *key)
{
	int		i;
	char	c;

	i = -1;
	if (!key || !(*key))
		return (0);
	if (key[0] == '%' || ft_isdigit(key[0]))
		return (0);
	while ((c = key[++i]))
	{
		if (ft_isalpha(c) || (c == '_' || c == '%'))
			continue;
		if (ft_isdigit(c))
			continue;
		return (0);
	}
	return (1);
}

static void	hash_import2(t_hash *root, char *envp, char *end, t_boolean force)
{
	char	*orig_envp;
	char	*temp;
	char	*value;
	char	*prefix;

	orig_envp = ft_strdup(envp);
	assert(orig_envp != NULL, "hash_import", ": Malloc error", 1);
	value = end + 1;
	prefix = NULL;
	*(end--) = '\0';
	if (*end == '+')
	{
		*(end--) = '\0';
		prefix = hash_get(root, envp);
	}
	if (!hash_verify_key(envp) && !force)
		print_err("hash_import", orig_envp, "not a valid identifier");
	else
	{
		temp = ft_strjoin(prefix, value);
		assert(temp != NULL, "hash_import", ": Malloc error", 1);
		hash_set(root, envp, temp);
		free(temp);
	}
	free(orig_envp);
}

void		hash_import(t_hash *root, char *envp, t_boolean force)
{
	char	*end;

	envp = ft_strdup(envp);
	assert(envp != NULL, "hash_import", ": Malloc error", 1);
	end = ft_strchr(envp, '=');
	if (!end)
	{
		if (!hash_verify_key(envp) && !force)
		{
			print_err("export", envp, "not a valid identifier");
			free(envp);
			return ;
		}
		if (!hash_has(root, envp))
			hash_set(root, envp, NULL);
		free(envp);
		return ;
	}
	hash_import2(root, envp, end, force);
	free(envp);
}

char		*hash_get_envp(t_hash *root, char *key)
{
	t_hash *hash;

	hash = hash_get_node(root, key, false);
	if (!hash || !hash->value)
		return (NULL);
	return (joinstring(hash->key, '=', hash->value));
}
