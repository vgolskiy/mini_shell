/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:49:25 by dchief            #+#    #+#             */
/*   Updated: 2020/11/08 15:09:19 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./common.h"
# include "./hash.h"

typedef struct	s_minishell
{
	int			shell_in_fd;
	int			shell_out_fd;
	t_hash		*environ;
	t_boolean	executing;
	t_boolean	running;
	t_boolean	interactive;
	t_boolean	isfromfile;
	char		*prompt;
	pid_t		pids[100];
}				t_mini_shell;

#endif
