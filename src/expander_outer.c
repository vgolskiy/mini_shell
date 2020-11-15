/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_outer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 17:42:16 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/executor.h"

void		resolve_env_node_value_outer(struct s_resolution_context *ctx,
				t_hash *node)
{
	char	*start;
	char	*cur;
	char	*laststr;

	start = node->value;
	if (ft_isspace(*start) && (ctx->list_sec && ctx->list_sec->count))
	{
		laststr = ctx->list_sec->last->value;
		if (ft_strlen(laststr) != 0)
			push_to_list(ctx->list_sec, ft_strdup(" "));
	}
	while (ft_isspace(*start))
		start++;
	while ((cur = get_next_space(start)))
	{
		push_to_list(ctx->list_sec, safe_clone(start, cur));
		push_to_list(ctx->list, concat_string(ctx->list_sec, true));
		ctx->list_sec = init_list();
		start = ++cur;
		while (ft_isspace(*start))
			start++;
	}
	push_to_list(ctx->list_sec, safe_clone(start, NULL));
}

void		resolve_environ_value_outer(struct s_resolution_context *ctx)
{
	char	letter;
	t_hash	*node;
	int		i;

	i = ctx->i;
	node = ctx->ex->shell->environ;
	if (ctx->t->context->cat[i] == '@')
		i++;
	while (ctx->t->context->cat[i] == '#')
	{
		letter = ctx->t->context->str[i++];
		if (!has_child(node, letter))
			return ;
		node = node->next[letter % 16][letter / 16];
	}
	if (!node->value)
		return ;
	resolve_env_node_value_outer(ctx, node);
}
