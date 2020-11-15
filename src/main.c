/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:54:54 by dchief            #+#    #+#             */
/*   Updated: 2020/11/13 21:36:53 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/common.h"
#include "../include/hash.h"
#include "../include/envp.h"
#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/executor.h"

int			main(int argc, char **argv, char **envp)
{
	t_ex	*ex;
	int		fd;

	if (argc >= 2)
	{
		fd = open(argv[1], O_RDONLY);
		dup2(fd, 0);
		close(fd);
	}
	ex = init_ex();
	hash_import_many(ex->shell->environ, envp);
	ex->user = hash_has(ex->shell->environ, "USER") ?
	ft_strdup(hash_get(ex->shell->environ, "USER")) :
	ft_strdup("Unauthorized");
	assert(ex->user != NULL, "hash_import",
		": Error allocating temporary memory", 1);
	hash_set(ex->shell->environ, "?", "0");
	getprompt(ex);
	setup_shell_pwd(ex);
	setup_shell_level(ex);
	handle_signal();
	while (ex->shell->running)
		repl(ex);
	hash_destroy(ex->shell->environ);
}
