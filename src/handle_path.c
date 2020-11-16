/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:01:05 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

char		**get_resolution_paths(t_hash *root)
{
	char *raw;
	char **tmp;

	raw = hash_get(root, "PATH");
	assert(raw != NULL, NULL,
			"PATH is empty: only builtin functions available", 127);
	tmp = ft_split(raw, ':');
	assert(tmp != NULL, "get_resolution_paths", ": Malloc error", 1);
	return (tmp);
}
