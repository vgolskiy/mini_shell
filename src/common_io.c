/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:42:04 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 15:42:33 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/common.h"
#include "../include/hash.h"
#include "../include/envp.h"
#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/executor.h"

t_boolean	ft_isatty(int fd)
{
	struct stat info;

	assert(fstat(fd, &info) >= 0, "ft_isatty", "Unexpected error", 1);
	return ((info.st_mode & 00170000) == 0020000);
}

t_boolean	ft_isafile(int fd)
{
	struct stat info;

	assert(fstat(fd, &info) >= 0, "ft_isafile", "Unexpected error", 1);
	return ((info.st_mode & 00170000) == 0100000);
}
