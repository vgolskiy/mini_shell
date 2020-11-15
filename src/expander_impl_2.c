/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_impl_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:27:04 by dchief            #+#    #+#             */
/*   Updated: 2020/11/11 00:35:33 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/executor.h"

void	resolve_argument_impl_cat_default(struct s_resolution_context *ctx)
{
	resolve_argument_impl_ensure_temp_string(ctx);
	*(ctx->cur++) = ctx->t->context->str[ctx->i];
	ctx->i++;
}

void	resolve_argument_impl_cat_dollar(struct s_resolution_context *ctx)
{
	resolve_argument_impl_flush_temp_string(ctx);
	resolve_environ_value(ctx);
	ctx->i++;
}

void	resolve_argument_impl_cat_at(struct s_resolution_context *ctx)
{
	resolve_argument_impl_flush_temp_string(ctx);
	resolve_environ_value_outer(ctx);
	ctx->i++;
}

void	resolve_argument_impl_cat_exclaim(struct s_resolution_context *ctx)
{
	resolve_argument_impl_flush_temp_string(ctx);
	push_to_list(ctx->list, concat_string_filtering_empty(ctx->list_sec));
	ctx->list_sec = init_list();
	ctx->i++;
}
