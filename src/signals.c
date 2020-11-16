/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:16:47 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 19:50:35 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"

static t_ex *g_ex;

static void	handler_sigint(int sig)
{
	if (g_ex->shell->executing && sig == SIGINT)
	{
		g_ex->shell->executing = false;
		hash_set(g_ex->shell->environ, "?", "130");
		write(1, "\b\b  \b\b", 6);
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

static void	handler(int sig)
{
	assert(g_ex != NULL, "SIG", "\nUnexpected error\n", 1);
	handler_sigint(sig);
	if (g_ex->shell->executing && sig == SIGQUIT)
	{
		g_ex->shell->executing = false;
		write(1, "\b\b  \b\b", 6);
		ft_putstr_fd("\nRunning command(s) coredumped\n", 2);
		return ;
	}
	if (!g_ex->shell->executing && sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
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
