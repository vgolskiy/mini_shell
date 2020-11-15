/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:38:56 by dchief            #+#    #+#             */
/*   Updated: 2020/11/15 18:34:04 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/executor.h"
#include "../include/envp.h"

void		repl_cleanup(t_ex *ex, t_lexer *my)
{
	ex->shell->executing = false;
	destory_tree(ex->root);
	lexer_destroy(my);
}

void		repl_check_pipeline_syntax(t_ex *ex)
{
	t_token	**cur;

	cur = ex->root->child;
	if ((*(cur +1)) == NULL && (*cur)->start == (*cur)->stop )
	{
		if (ex->shell->executing)
			ft_putendl_fd("Incorrect syntax", 2);
		ex->shell->executing = false;
		kill_all_pipeline(ex);
	}
	while (cur && *cur && *(cur + 1))
	{
		if ((*cur)->child[0] == NULL)
		{
			if (ex->shell->executing)
				ft_putendl_fd("Incorrect syntax", 2);
			ex->shell->executing = false;
			kill_all_pipeline(ex);
		}
		cur++;
	}
}

t_boolean	repl(t_ex *ex)
{
	char	*input;
	t_lexer	*my;
	t_token	**cur;

	input = linegetter(getprompt(ex), ex);
	if (input == NULL)
	{
		ex->shell->running = false;
		return (0);
	}
	my = init_parser(input);
	ex->root = create_root(my);
	ex->shell->executing = true;
	repl_check_pipeline_syntax(ex);
	cur = ex->root->child;
	while (cur && *cur && ex->shell->executing)
		process_pipeline(*(cur++), ex);
	repl_cleanup(ex, my);
	return (true);
}
