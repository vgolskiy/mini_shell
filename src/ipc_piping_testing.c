/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_piping_testing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:34:54 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 15:35:07 by dchief           ###   ########.fr       */
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

void	test_process_forward(char *line, t_ex *ex)
{
	char *file;

	file = line;
	while (*file && *file == '<')
		file++;
	while (*file && *file == '>')
		file++;
	while (*file && ft_isspace(*file))
		file++;
	if (ft_strlen(file) == 0)
	{
		ex->shell->executing = false;
		ft_putendl_fd("minishell: syntax error", 2);
		hash_set(ex->shell->environ, "?", "2");
	}
}

void	test_syntax_command(t_token *t, t_ex *ex)
{
	t_resolved	result;
	int			j;

	cheanup_ex(ex);
	result = resolve_arguments_redirects(t, ex);
	ex->process = result;
	j = 0;
	while (ex->process.fwd[j] && ex->shell->executing)
		test_process_forward(ex->process.fwd[j++], ex);
	if (*(t->child) == NULL)
	{
		ex->shell->executing = false;
		ft_putendl_fd("minishell:syntax error near unexpected token `|'", 2);
		hash_set(ex->shell->environ, "?", "2");
		return ;
	}
}

void	test_syntax_pipeline(t_token *t, t_ex *ex)
{
	t_token	**cur;

	cur = t->child;
	while (cur && *cur && (ex->command = *cur) && ex->shell->executing)
	{
		test_syntax_command(*cur, ex);
		cur++;
	}
}
