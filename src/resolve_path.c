/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/09 20:56:09 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

char			*create_executable(char *path, char *cmd)
{
	t_lst *list;

	list = init_list();
	push_to_list(list, path);
	push_to_list(list, "/");
	push_to_list(list, cmd);
	return (concat_string(list, false));
}

static void		noop(void)
{
}

int				resolve_path_step(char *buffer)
{
	char *middle;
	char *beg;
	char *end;

	middle = buffer;
	while (*middle)
	{
		if (ft_strncmp(middle, "/../", 4) == 0)
			break ;
		middle++;
	}
	if (!*middle)
		return (0);
	beg = middle;
	end = middle;
	if (beg != buffer)
		while ((--beg >= buffer) && (*beg != '/'))
			noop();
	while (end && *(++end) && (*end != '/'))
		noop();
	if ((*beg != '/') || (*end != '/'))
		return (-1);
	while (beg && end && (end < buffer + PATH_MAX))
		*(beg++) = *(end++);
	return (1);
}

char			*resolve_fullpath(char *cmd)
{
	int		i;
	char	buffer[PATH_MAX];

	if (!cmd)
		return (NULL);
	ft_memset(buffer, '\0', PATH_MAX);
	ft_memcpy(buffer, cmd, ft_strlen(cmd));
	free(cmd);
	while ((i = resolve_path_step(buffer)) == 1)
	{
	}
	if (i == -1)
		return (NULL);
	return (ft_strdup(buffer));
}

char			*check_file_exists(char *cmd)
{
	struct stat buf;

	if (!cmd)
		return (NULL);
	if (stat(cmd, &buf) == 0)
		return (cmd);
	free(cmd);
	return (NULL);
}
