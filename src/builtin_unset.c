/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:30:59 by dchief            #+#    #+#             */
/*   Updated: 2020/11/15 19:23:47 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

int				ft_unset(t_ex *ex)
{
	int		i;
	char	*key;

	i = 0;
	while ((key = ex->process.argv[++i]))
	{
		if ((key) && (!ft_strchr(key, '=')) && hash_verify_key(key))
		{
			hash_unset(ex->shell->environ, key);
		}
		else
		{
			ft_putstr_fd(key, 2);
			ft_putendl_fd(": not a valid identifier", 2);
		}
	}
	return (1);
}
