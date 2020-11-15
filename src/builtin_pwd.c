/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:18:13 by dchief            #+#    #+#             */
/*   Updated: 2020/11/11 12:13:42 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

int	ft_pwd(t_ex *ex)
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	assert(tmp != NULL, "getcwd", ": Error allocating temporary memory", 1);
	(void)ex;
	ft_putstr(tmp);
	free(tmp);
	ft_putchar('\n');
	return (1);
}
