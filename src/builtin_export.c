/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:29:45 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:10:29 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

static void	put_escapedstr(char *value)
{
	while (*value)
	{
		if (*value == '\\')
		{
			ft_putchar(*value);
		}
		ft_putchar(*value);
		value++;
	}
}

static void	print_export(char *key, char *value)
{
	int klen;

	klen = (int)ft_strlen(key);
	if (klen > 2 && key[klen - 2] == '%' && key[klen - 1] == '%')
		return ;
	if (key[0] == '?')
		return ;
	if ((ft_strcmp(key, "_") == 0) || (ft_strcmp(key, "?") == 0))
		return ;
	ft_putstr("declare -x ");
	ft_putstr(key);
	if (value)
	{
		ft_putstr("=\"");
		put_escapedstr(value);
		ft_putstr("\"");
	}
	ft_putstr("\n");
}

int			ft_export(t_ex *ex)
{
	char	*env;
	int		i;
	int		code;

	if (ex->process.argc == 1)
	{
		hash_iterate(ex->shell->environ, print_export);
		return (0);
	}
	i = 0;
	code = 0;
	while (++i < ex->process.argc)
	{
		env = ex->process.argv[i];
		if (env[0] == '=')
		{
			print_err("hash_import", "=", "not a valid identifier");
			code = -1;
			continue ;
		}
		if (ex->is_single_cmd_pipeline)
			hash_import(ex->shell->environ, env, false);
		if (ex->process.envp)
			stringlist_destroy(ex->process.envp);
		ex->process.envp = hash_to_envp(ex->shell->environ);
	}
	return (code);
}
