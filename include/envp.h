/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:37:21 by dchief            #+#    #+#             */
/*   Updated: 2020/10/28 16:07:53 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "./hash.h"

void	hash_import(t_hash *root, char *envp);
char	*hash_get_envp(t_hash *root, char *key);
char	**hash_to_envp(t_hash *root);
void	stringlist_destroy(char **list);

#endif
