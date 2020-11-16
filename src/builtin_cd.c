/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:43:50 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/15 23:37:37 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"
#include "../include/hash.h"

char	*resolve_newpwd(t_ex *ex)
{
	char *nextpwd;

	if (ex->process.argc == 1 || ft_strcmp(ex->process.argv[1], "~") == 0)
	{
		if (!(nextpwd = hash_get(ex->shell->environ, "HOME")))
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			hash_set(ex->shell->environ, "?", "1");
		}
	}
	else if (ft_strcmp(ex->process.argv[1], "-") == 0)
	{
		nextpwd = hash_get(ex->shell->environ, "OLDPWD");
		ft_putendl_fd(nextpwd, 1);
	}
	else
		nextpwd = ex->process.argv[1];
	return (nextpwd);
}

void	print_err(char *msg1, char *variable, char *msg2)
{
	char	*delimeter;

	delimeter = ": ";
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(delimeter, 2);
	ft_putstr_fd(variable, 2);
	ft_putstr_fd(delimeter, 2);
	ft_putendl_fd(msg2, 2);
}

static void ft_cd_update_state(t_ex *ex, char *oldpwd) {
	char	*nextpwd;

	nextpwd = getcwd(NULL, 0);
	if (ex->is_single_cmd_pipeline && !oldpwd)
		hash_set(ex->shell->environ, "PWD", nextpwd);
	if (ex->is_single_cmd_pipeline && oldpwd)
		hash_set2(ex->shell->environ, (t_pair){"OLDPWD", oldpwd},
					(t_pair){"PWD", nextpwd});
	free(nextpwd);
}

int		ft_cd(t_ex *ex)
{
	char	*oldpwd;
	char	*nextpwd;

	if (ex->process.argc > 2)
	{
		ft_putendl_fd("cd: Too many arguments", 2);
		return (-1);
	}
	nextpwd = resolve_newpwd(ex);
	oldpwd = hash_get(ex->shell->environ, "PWD");
	if (!nextpwd)
		return (-1);
	if (chdir(nextpwd) < 0)
	{
		print_err("cd", nextpwd, strerror(errno));
		return (-1);
	}
	ft_cd_update_state(ex, oldpwd);
	return (1);
}
