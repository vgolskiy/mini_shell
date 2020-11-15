/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_children.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:33:59 by dchief            #+#    #+#             */
/*   Updated: 2020/11/08 17:31:56 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/envp.h"
#include "../include/executor.h"

t_token		*create_childen_next_token(t_token *parent, int start)
{
	enum e_token_type o;

	o = parent->type;
	if (o == ROOT)
		return (create_part(parent, start));
	if (o == PART)
		return (create_exec(parent, start));
	if (o == EXEC)
		return (create_word(parent, start));
	return (NULL);
}

void		create_childen(t_token *parent)
{
	t_token	**cur;
	int		start;
	t_lst	*list;
	t_token	*next;

	start = parent->start;
	list = init_list();
	while (start < parent->stop)
	{
		next = create_childen_next_token(parent, start);
		if (!next)
			break ;
		push_to_list(list, next);
		start = next->stop;
	}
	parent->child = (t_token **)to_array(list);
	cur = parent->child;
	while (cur && *cur)
		create_childen(*(cur++));
}

t_token		*create_token(t_lexer *context, enum e_token_type type,
						int start, int stop)
{
	t_token *t;

	t = malloc(sizeof(t_token));
	assert(t != NULL, "create_token", "Error allocating memory", 1);
	t->context = context;
	t->type = type;
	t->start = start;
	t->stop = stop;
	t->child = NULL;
	return (t);
}
