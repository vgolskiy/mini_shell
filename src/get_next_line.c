/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 23:58:05 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/02 22:38:39 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

static void	ft_free(char *left)
{
	if (left)
	{
		free(left);
		left = 00;
	}
}

static char	*add_char(char **s, char ch)
{
	int		i;
	int		j;
	char	*res;

	if (!(res = ft_calloc(ft_strlen_gnl(*s) + 2, sizeof(char))))
		return (00);
	i = 0;
	j = -1;
	while ((*s) && ((*s)[++j]))
		res[i++] = (*s)[j];
	ft_free(*s);
	res[i] = ch == '\n' ? '\0' : ch;
	return (res);
}

static int	ft_error(char *left)
{
	ft_free(left);
	return (-1);
}

int			get_next_line(char **line, int fd)
{
	int		readed_bytes;
	char	*left;
	char	buf[1];

	left = 00;
	while ((readed_bytes = (int)read(fd, buf, 1)) > 0)
	{
		if (!(left = add_char(&left, buf[0])))
			return (ft_error(left));
		if (buf[0] == '\n')
		{
			*line = left;
			return (1);
		}
	}
	if (readed_bytes < 0)
		return (ft_error(left));
	*line = left;
	return (0);
}
