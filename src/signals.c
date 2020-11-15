/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:16:47 by dchief            #+#    #+#             */
/*   Updated: 2020/11/13 19:42:28 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static t_ex *g_ex;

static void	handler(int sig)
{
	assert(g_ex != NULL, "SIG", "\nUnexpected error\n", 1);
	if (g_ex->shell->executing && sig == SIGINT)
	{
		g_ex->shell->executing = false;
		hash_set(g_ex->shell->environ, "?", "130");
		write(1, "\b\b  \b\b", 6);
		//ft_putstr_fd("\nRunning command(s) aborted\n", 2);
		return ;
	}
	if (g_ex->shell->executing && sig == SIGQUIT)
	{
		g_ex->shell->executing = false;
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\nRunning command(s) coredumped\n", 2);
		return ;
	}
	if (!g_ex->shell->executing && sig == SIGQUIT)
	{
		//ft_putstr_fd("\nNothing is running right now\n", 2);
		write(1, "\b\b  \b\b", 6);
		//ft_putstr_fd(getprompt(g_ex), 2);
		return ;
	}
	if (!g_ex->shell->executing && sig == SIGINT)
	{
		hash_set(g_ex->shell->environ, "?", "1");
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(getprompt(g_ex), 2);
	}
}

void		setup_global_ex(t_ex *ex)
{
	g_ex = ex;
}

void		handle_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handler);
	signal(SIGTSTP, SIG_IGN);
}

void		reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}
