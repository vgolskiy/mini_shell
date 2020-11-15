/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:43:50 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/05 22:28:57 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

t_builtin_cmd	get_builtin_by_name(char *cmd)
{
	t_builtin_cmd			*current;
	static t_builtin_cmd	builtins[] = {
		{"echo", ft_echo},
		{"pwd", ft_pwd},
		{"env", ft_env},
		{"cd", ft_cd},
		{"export", ft_export},
		{"declare", ft_declare},
		{"unset", ft_unset},
		{"exit", ft_exit},
		{NULL, NULL}};

	if (!cmd)
		return ((t_builtin_cmd){NULL, NULL});
	current = builtins;
	while (current->name)
	{
		if (ft_strcmp(current->name, cmd) == 0)
			return (*current);
		current++;
	}
	return ((t_builtin_cmd){NULL, NULL});
}
