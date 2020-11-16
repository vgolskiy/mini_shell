/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_features.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:40:24 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:01:05 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/common.h"
#include "../include/hash.h"
#include "../include/envp.h"
#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/executor.h"

t_ex		*init_ex(void)
{
	t_ex *ex;

	ex = malloc(sizeof(t_ex));
	assert(ex != NULL, "init_ex", ": Malloc error", 1);
	ex->process.fwd = NULL;
	ex->process.argv = NULL;
	ex->process.envp = NULL;
	ex->user = NULL;
	ex->shell = malloc(sizeof(t_mini_shell));
	assert(ex->shell != NULL, "init_ex", ": Malloc error", 1);
	ex->shell->running = true;
	ex->shell->executing = false;
	ex->shell->interactive = ft_isatty(0);
	ex->shell->isfromfile = ft_isafile(0);
	ex->shell->shell_in_fd = dup(0);
	ex->shell->shell_out_fd = dup(1);
	ex->shell->environ = hash_create_node();
	ex->shell->prompt = NULL;
	setup_global_ex(ex);
	return (ex);
}

void		hash_import_many(t_hash *root, char **envp)
{
	char **c;

	c = envp;
	while (*c)
	{
		hash_import(root, *c, true);
		c++;
	}
}

void		setup_shell_pwd(t_ex *ex)
{
	hash_set(ex->shell->environ, "PWD", ex->path);
	if (!hash_has(ex->shell->environ, "OLDPWD"))
	{
		hash_set(ex->shell->environ, "OLDPWD", NULL);
	}
}

void		setup_shell_level(t_ex *ex)
{
	char	*shlvl;
	int		d;

	shlvl = hash_get(ex->shell->environ, "SHLVL");
	if (shlvl)
	{
		d = ft_atoi(shlvl) + 1;
		shlvl = ft_itoa(d);
		hash_set(ex->shell->environ, "SHLVL", shlvl);
		free(shlvl);
	}
	else
	{
		hash_set(ex->shell->environ, "SHLVL", "1");
	}
}
