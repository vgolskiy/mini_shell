/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_piping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:17:23 by dchief            #+#    #+#             */
/*   Updated: 2020/11/15 20:29:45 by dchief           ###   ########.fr       */
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

void	cheanup_ex(t_ex *ex)
{
	if (ex->process.envp)
		stringlist_destroy(ex->process.envp);
	if (ex->process.argv)
		stringlist_destroy(ex->process.argv);
	if (ex->process.fwd)
		stringlist_destroy(ex->process.fwd);
	ex->process.envp = NULL;
	ex->process.argv = NULL;
	ex->process.fwd = NULL;
}

void	process_forwards(t_token *t, t_ex *ex)
{
	t_resolved	result;
	int			i;

	cheanup_ex(ex);
	result = resolve_arguments_redirects(t, ex);
	ex->process = result;
	i = 0;
	while (ex->process.fwd[i])
		process_forward(ex->process.fwd[i++]);
}

void	process_command(t_token *t, t_ex *ex)
{
	int			i;
	pid_t		pid;
	char		*last;

	process_forwards(t, ex);
	last = NULL;
	if (ex->process.argc > 0)
		last = ex->process.argv[ex->process.argc - 1];
	if (*(t->child) == NULL)
	{
		ex->shell->executing = false;
		kill_all_pipeline(ex);
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return ;
	}
	if (last)
		hash_set(ex->shell->environ, "_", last);
	pid = handle_fork(ex->process.argv[0], ex);
	i = 0;
	while ((i < 100) && ex->shell->pids[i])
		i++;
	assert(ex->shell->pids[i] == 0, "pid", "Too many pipes", 1);
	ex->shell->pids[i] = pid;
}

void	reset_state(t_ex *ex)
{
	ex->pipeline = NULL;
	ex->is_single_cmd_pipeline = false;
	ex->command = NULL;
	dup2(ex->shell->shell_in_fd, 0);
	dup2(ex->shell->shell_out_fd, 1);
}

void	process_pipeline(t_token *t, t_ex *ex)
{
	t_token	**cur;
	int		pipefd[2];
	int		i;

	test_syntax_pipeline(t, ex);
	i = 100;
	while (--i >= 0)
		ex->shell->pids[i] = 0;
	ex->pipeline = t;
	ex->is_single_cmd_pipeline = (count_cmds(ex) == 1);
	ft_putnbr_fd(count_cmds(ex),2);
	ft_putendl_fd("parasha", 2);
	cur = t->child;
	while (cur && *cur && (ex->command = *cur) && ex->shell->executing)
	{
		setup_input_pipe_fd(t, *cur, pipefd, ex);
		setup_output_pipe_fd(t, *cur, pipefd, ex);
		process_command(*cur, ex);
		cur++;
	}
	reset_state(ex);
	wait_for_all_cmds(ex);
}
