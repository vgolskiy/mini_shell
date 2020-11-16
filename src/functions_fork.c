/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:27:06 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/16 19:59:11 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

char			*resolve_binary(char *path, char *cmd)
{
	char	*fullpath;

	if (cmd)
		fullpath = create_executable(path, cmd);
	else
		fullpath = ft_strdup(path);
	fullpath = resolve_fullpath(fullpath);
	fullpath = check_file_exists(fullpath);
	return (fullpath);
}

static char		*get_path_global(char *cmd)
{
	char	*fullpath;

	fullpath = resolve_binary(cmd, NULL);
	if (fullpath)
		return (fullpath);
	return (cmd);
}

static char		*get_path(char *cmd, t_ex *ex)
{
	char	**paths;
	int		i;
	char	*fullpath;

	if (cmd[0] == '/')
	{
		return (get_path_global(cmd));
	}
	fullpath = resolve_binary(ex->path, cmd);
	if (fullpath)
		return (fullpath);
	if (ft_strchr(cmd, '/'))
		return (NULL);
	paths = get_resolution_paths(ex->shell->environ);
	i = -1;
	while (paths[++i])
	{
		fullpath = resolve_binary(paths[i], cmd);
		if (fullpath)
			break ;
	}
	stringlist_destroy(paths);
	return (fullpath);
}

char			*handle_fork_get_cmd_abs(char *cmd, t_ex *ex)
{
	char			*cmd_abs;

	cmd_abs = get_path(cmd, ex);
	if (cmd_abs)
	{
		hash_set(ex->shell->environ, "_", cmd_abs);
		free(cmd_abs);
		cmd_abs = hash_get(ex->shell->environ, "_");
	}
	assert(cmd_abs != NULL, cmd, ": command not found", 127);
	return (cmd_abs);
}

int				handle_fork(char *cmd, t_ex *ex)
{
	t_builtin_cmd	current;
	pid_t			pid;
	char			*cmd_abs;
	int				code;

	refresh_envp(ex);
	current = get_builtin_by_name(cmd);
	if (current.fn)
	{
		code = current.fn(ex);
		if (code > 0)
			code = 0;
		set_success_code(ex, -code);
		return (0);
	}
	pid = fork();
	assert(pid >= 0, "minishell", "Falied to fork process", 1);
	if (pid > 0)
		return (pid);
	cmd_abs = handle_fork_get_cmd_abs(cmd, ex);
	refresh_envp(ex);
	reset_signal();
	execve(cmd_abs, ex->process.argv, ex->process.envp);
	assert(false, cmd, ": command not found", 127);
	return (0);
}
