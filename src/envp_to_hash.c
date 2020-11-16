/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:24:34 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 10:19:28 by mskinner         ###   ########.fr       */
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
	int i;
	char c;

	i = -1;
	if (!key || !(*key))
		return (0);
	if (key[0] == '%' || ft_isdigit(key[0]))
		return (0);
	while ((c = key[++i]))
	{
		if (ft_isalpha(c) || (c == '_' || c == '%')) {
			continue;
		}
		if (ft_isdigit(c)) {
			continue;
		}
		return 0;
	}
	return (1);
}

static void	hash_import2(t_hash *root, char *envp, char *end, t_boolean force)
{
	char	*temp;
	char	*value;
	char	*prefix;

	value = end + 1;
	prefix = NULL;
	*(end--) = '\0';
	if (*end == '+')
	{
		*(end--) = '\0';
		prefix = hash_get(root, envp);
	}
	if ((ft_strchr(envp, '+') || (ft_strlen(envp) == 0) || (hash_verify_key(envp) == 0))
	&& !force)
		print_err("hash_import", envp, "not a valid identifier");
	else
	{
		temp = ft_strjoin(prefix, value);
		assert(temp != NULL, "hash_import",
			": Error allocating temporary memory", 1);
		hash_set(root, envp, temp);
		free(temp);
	}
}

void		hash_import(t_hash *root, char *envp, t_boolean force)
{
	char	*temp2;
	char	*end;

	envp = ft_strdup(envp);
	assert(envp != NULL, "hash_import",
			": Error allocating temporary memory", 1);
	end = ft_strchr(envp, '=');
	if (!end)
	{
		if (!hash_verify_key(envp) && !force)
		{
			print_err("export", envp, "not a valid identifier");
			free(envp);
			return;
		}
		if (!hash_has(root, envp))
			hash_set(root, envp, NULL);
		free(envp);
		return ;
	}
	temp2 = ft_strdup(envp);
	hash_import2(root, envp, end, force);
	free(envp);
	free(temp2);
}

char		*hash_get_envp(t_hash *root, char *key)
{
	t_hash *hash;

	hash = hash_get_node(root, key, false);
	if (!hash || !hash->value)
		return (NULL);
	return (joinstring(hash->key, '=', hash->value));
}
