/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:37:21 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 20:00:06 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "./hash.h"

char	*hash_get_envp(t_hash *root, char *key);
char	**hash_to_envp(t_hash *root);
void	stringlist_destroy(char **list);
int		hash_verify_key(char *key);
void	hash_import_many(t_hash *root, char **envp);

#endif
