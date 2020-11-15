/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 13:43:50 by mskinner          #+#    #+#             */
/*   Updated: 2020/10/31 02:32:38 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

int				ft_echo(t_ex *ex)
{
	char		**rest;
	t_boolean	flag;

	rest = ex->process.argv + 1;
	flag = false;
	while (rest && *rest && ft_strcmp(*rest, "-n") == 0)
	{
		flag = true;
		rest++;
	}
	while (*rest)
	{
		ft_putstr(*(rest++));
		if (*rest)
			ft_putstr(" ");
	}
	if (!flag)
		ft_putchar('\n');
	return (1);
}
