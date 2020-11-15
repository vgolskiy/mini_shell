/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:25:43 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 17:29:18 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/executor.h"

struct s_resolution_context	*init_resolution_context(t_token *t,
												t_ex *ex, t_lst *list)
{
	struct s_resolution_context *ctx;

	ctx = malloc(sizeof(struct s_resolution_context));
	ctx->cur = NULL;
	ctx->tmp = NULL;
	ctx->t = t;
	ctx->i = t->start;
	ctx->list_sec = init_list();
	ctx->list = list;
	ctx->ex = ex;
	return (ctx);
}

void						*resolve_argument(t_token *t, t_ex *ex,
							t_lst *list)
{
	struct s_resolution_context *ctx;

	ctx = init_resolution_context(t, ex, list);
	assert(ctx != NULL, "resolve_argument",
					"Error allocating temporary memory", 1);
	resolve_argument_impl(ctx);
	free(ctx);
	return (0);
}
