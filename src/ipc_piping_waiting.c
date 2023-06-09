/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_piping_waiting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:36:00 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 14:03:36 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/common.h"
#include "../include/hash.h"
#include "../include/envp.h"
#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/executor.h"
#include <sys/wait.h>

void	wait_for_all_cmds(t_ex *ex)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < 100)
	{
		pid = ex->shell->pids[i];
		if (pid)
			wait_for_pipeline(pid, ex);
		ex->shell->pids[i] = 0;
		i++;
	}
}

int		count_cmds(t_ex *ex)
{
	t_token	**cur;
	int		i;

	i = 0;
	cur = ex->pipeline->child;
	while (cur && *cur)
	{
		cur++;
		i++;
	}
	return (i);
}

void	wait_for_pipeline(pid_t pid, t_ex *ex)
{
	int		status;
	char	*x;

	waitpid(pid, &status, 0);
	if ((status & 0x7f) == 0)
	{
		x = ft_itoa((status & 0xff00) >> 8);
		assert(x != NULL, "waitpid", "Malloc error", 1);
		hash_set(ex->shell->environ, "?", x);
		free(x);
	}
}

void	kill_all_pipeline(t_ex *ex)
{
	int		i;
	pid_t	pid;

	ex->shell->executing = false;
	i = 0;
	while (i < 100)
	{
		pid = ex->shell->pids[i];
		if (pid)
			kill(pid, 9);
		ex->shell->pids[i] = 0;
		i++;
	}
}
