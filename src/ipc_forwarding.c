/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ipc_forwarding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 14:17:23 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 19:28:55 by mskinner         ###   ########.fr       */
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

void	apply_forward(char *file, int fg, int mode, int io)
{
	int fd;

	fd = open(file, fg, mode);
	if (fd > 0)
	{
		dup2(fd, io);
		close(fd);
	}
	else
	{
		if (file)
			ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
}

void	process_forward(char *line)
{
	char *file;

	file = line;
	while (*file && *file == '<')
		file++;
	while (*file && *file == '>')
		file++;
	while (*file && ft_isspace(*file))
		file++;
	if (ft_strncmp(">>", line, 2) == 0)
	{
		apply_forward(file, O_CREAT | O_APPEND | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 1);
	}
	else if (ft_strncmp(">", line, 1) == 0)
	{
		apply_forward(file, O_CREAT | O_TRUNC | O_WRONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, 1);
	}
	else if (ft_strncmp("<", line, 1) == 0)
	{
		apply_forward(file, O_RDONLY, 0, 0);
	}
}

void	setup_input_pipe_fd(t_token *pipeline, t_token *command,
						int *pipefd, t_ex *ex)
{
	t_token	*first;
	int		fd_in;

	first = pipeline->child ? pipeline->child[0] : NULL;
	if (command == first)
	{
		fd_in = dup(ex->shell->shell_in_fd);
	}
	else
	{
		fd_in = pipefd[0];
	}
	dup2(fd_in, 0);
	close(fd_in);
}

void	setup_output_pipe_fd(t_token *pipeline,
						t_token *command, int *pipefd, t_ex *ex)
{
	int		i;
	t_token	*last;
	int		fd_out;

	i = 0;
	last = NULL;
	while (pipeline->child && pipeline->child[i])
	{
		last = pipeline->child[i++];
	}
	if (command == last)
	{
		fd_out = dup(ex->shell->shell_out_fd);
	}
	else
	{
		pipe(pipefd);
		fd_out = pipefd[1];
	}
	dup2(fd_out, 1);
	close(fd_out);
}
