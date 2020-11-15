/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 22:40:40 by dchief            #+#    #+#             */
/*   Updated: 2020/11/06 11:27:47 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/common.h"

void	assert(t_boolean ok, char *context, char *message, int code)
{
	if (ok)
		return ;
	if (context)
		ft_putstr_fd(context, 2);
	if (context)
		ft_putchar_fd(' ', 2);
	if (message)
		ft_putendl_fd(message, 2);
	exit(code);
}
