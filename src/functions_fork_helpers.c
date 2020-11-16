/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_fork_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:57:36 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 19:59:33 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

void		set_success_code(t_ex *ex, int code)
{
	char *tmp;

	tmp = ft_itoa(code);
	assert(tmp != NULL, "set_success_code", "Malloc error", 2);
	hash_set(ex->shell->environ, "?", tmp);
	free(tmp);
}

void		refresh_envp(t_ex *ex)
{
	if (ex->process.envp)
		stringlist_destroy(ex->process.envp);
	ex->process.envp = hash_to_envp(ex->shell->environ);
}
