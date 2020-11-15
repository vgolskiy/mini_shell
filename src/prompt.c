/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:20:50 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/13 21:37:08 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

static char	*get_last_segment(char *cwd)
{
	char	*r;
	char	*p;

	p = cwd;
	if (ft_strlen((r = cwd)) == 1)
		return (r);
	while (*p)
		if (*(p++) == '/')
			r = p;
	return (r);
}

char		*getprompt(t_ex *ex)
{
	t_lst	*list;
	char	*home;

	list = init_list();
	home = hash_get(ex->shell->environ, "HOME");
	if (!list || !getcwd(ex->path, sizeof(ex->path)))
	{
		ft_putendl_fd(strerror(errno), 2);
		return (NULL);
	}
	push_to_list(list, "shell_21:");
	if (home && (ft_strcmp(home, ex->path) == 0))
		push_to_list(list, "~");
	else
		push_to_list(list, get_last_segment(ex->path));
	push_to_list3(list, " ", ex->user, "$ ");
	if (ex->shell->prompt)
		free(ex->shell->prompt);
	ex->shell->prompt = concat_string(list, false);
	return (ex->shell->prompt);
}

void		env_fd(t_hash *root, int fd)
{
	char	**envp;
	char	**c;

	envp = hash_to_envp(root);
	c = envp;
	while (*c)
	{
		ft_putstr_fd(*c, fd);
		ft_putchar_fd('\n', fd);
		c++;
	}
	stringlist_destroy(envp);
}

char		*linegetter(char *prompt, t_ex *ex)
{
	char	*input;

	input = NULL;
	if (ex->shell->interactive)
		ft_putstr_fd(prompt, 2);
	if (get_next_line(&input, STDIN_FILENO) == -1)
		return (NULL);
	return (input);
}
