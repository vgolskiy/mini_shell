/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:43:50 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/11 16:11:00 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

static void	print_env(char *key, char *value)
{
	if (!value)
		return ;
	if (key[0] == '?')
		return ;
	ft_putstr(key);
	ft_putstr("=");
	ft_putstr(value);
	ft_putstr("\n");
}

int			ft_env(t_ex *ex)
{
	int i;
	int code;

	if (ex->process.argc == 1)
	{
		hash_iterate(ex->shell->environ, print_env);
		return (1);
	}
	i = 0;
	code = 0;
	while (ex->process.argv[++i])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(ex->process.argv[i], 2);
		ft_putendl_fd(": No such file or directory", 2);
		code = -1;
	}
	return (code);
}
