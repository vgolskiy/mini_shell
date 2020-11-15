/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:38:29 by dchief            #+#    #+#             */
/*   Updated: 2020/11/06 17:30:03 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/executor.h"

t_token		*create_root(t_lexer *context)
{
	t_token *root;

	root = create_token(context, ROOT, 0, context->len);
	create_childen(root);
	return (root);
}

char		**resolve_arguments(t_token *p, t_ex *ex)
{
	t_lst	*list_arguments;
	t_token	**c;
	t_token	*t;

	list_arguments = init_list();
	c = p->child;
	while (c && (t = *(c++)))
	{
		if (t && (t->type == WORD))
			resolve_argument(t, ex, list_arguments);
	}
	return ((char **)to_array(list_arguments));
}

char		**resolve_redirects(t_token *p, t_ex *ex)
{
	t_lst	*list_redirects;
	t_token	**c;
	t_token	*t;

	list_redirects = init_list();
	c = p->child;
	while (c && (t = *(c++)))
	{
		if (t && (t->type == IO))
			resolve_argument(t, ex, list_redirects);
	}
	return ((char **)to_array(list_redirects));
}

t_resolved	resolve_arguments_redirects(t_token *p, t_ex *ex)
{
	char	**argv;
	char	**fwrd;
	char	**envp;
	int		argc;

	argv = resolve_arguments(p, ex);
	fwrd = resolve_redirects(p, ex);
	envp = (char **)hash_to_envp(ex->shell->environ);
	argc = 0;
	while (argv[argc])
		argc++;
	return (t_resolved){argv, fwrd, envp, argc};
}

void		destory_tree(t_token *token)
{
	t_token **child;
	t_token *curr;

	child = token->child;
	while ((curr = *(child++)))
		destory_tree(curr);
	if (token->child)
		free(token->child);
	free(token);
}
