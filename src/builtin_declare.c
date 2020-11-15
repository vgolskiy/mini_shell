/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_declare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:29:45 by dchief            #+#    #+#             */
/*   Updated: 2020/11/15 19:52:13 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

int				ft_declare(t_ex *ex)
{
	char	*env;
	char	*flag;
	int		i;

	i = 1;
	while (i < ex->process.argc)
	{
		flag = ex->process.argv[i];
		if (flag[0] != '-')
			break ;
		i++;
	}
	while (i < ex->process.argc)
	{
		env = ex->process.argv[i];
		if (env[0] != '=')
			hash_import(ex->shell->environ, env, false);
		i++;
	}
	if (ex->process.envp)
		stringlist_destroy(ex->process.envp);
	ex->process.envp = hash_to_envp(ex->shell->environ);
	return (1);
}
