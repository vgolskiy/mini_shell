/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:18:13 by dchief            #+#    #+#             */
/*   Updated: 2020/11/16 13:59:24 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

int	ft_pwd(t_ex *ex)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	assert(tmp != NULL, "getcwd", ": Malloc error", 1);
	(void)ex;
	ft_putstr(tmp);
	free(tmp);
	ft_putchar('\n');
	return (0);
}
