/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_impl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:24:41 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 18:45:42 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/executor.h"

void	resolve_argument_impl_cat_skipping(struct s_resolution_context *ctx)
{
	ctx->i++;
}

void	resolve_argument_impl_flush_temp_string(struct s_resolution_context
		*ctx)
{
	if (ctx->tmp)
		push_to_list(ctx->list_sec, ctx->tmp);
	ctx->tmp = NULL;
	ctx->cur = NULL;
}

void	resolve_argument_impl_ensure_temp_string(struct
			s_resolution_context *ctx)
{
	if (ctx->cur == NULL)
	{
		ctx->cur = temp_string(ctx->t->stop - ctx->t->start + 1);
		ctx->tmp = ctx->cur;
	}
}

void	resolve_argument_impl_step(struct s_resolution_context *ctx)
{
	if (ctx->t->context->cat[ctx->i] == '$')
		return (resolve_argument_impl_cat_dollar(ctx));
	if (ctx->t->context->cat[ctx->i] == '!')
		return (resolve_argument_impl_cat_exclaim(ctx));
	if (ctx->t->context->cat[ctx->i] == '@')
		return (resolve_argument_impl_cat_at(ctx));
	if (ctx->t->context->cat[ctx->i] == '.')
		return (resolve_argument_impl_cat_skipping(ctx));
	if (ctx->t->context->cat[ctx->i] == '#')
		return (resolve_argument_impl_cat_skipping(ctx));
	resolve_argument_impl_cat_default(ctx);
}

void	resolve_argument_impl(struct s_resolution_context *ctx)
{
	while (ctx->i < ctx->t->stop)
		resolve_argument_impl_step(ctx);
	resolve_argument_impl_flush_temp_string(ctx);
	push_to_list(ctx->list, concat_string_filtering_empty(ctx->list_sec));
}
