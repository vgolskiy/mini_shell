/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:53:46 by dchief            #+#    #+#             */
/*   Updated: 2020/11/08 15:10:05 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./common.h"
# include "./hash.h"

typedef struct	s_lexer
{
	char		*str;
	char		*cat;
	char		*stt;
	int			len;
	char		state;
	int			pos;
}				t_lexer;

t_boolean		is_valid_in_identifier(char c);
t_boolean		is_special(char c);
t_boolean		is_redirection(char c);
t_boolean		is_text_cat(char c);
t_lexer			*init_parser(char *input);

void			mark_special(t_lexer *p);
void			mark_escape(t_lexer *p);
void			mark_identifier(t_lexer *p, char x);
void			mark_letter(t_lexer *p);
void			enter_state(t_lexer *p);
void			leave_state(t_lexer *p);

void			lexer_set_next(t_lexer *p, char cat);

#endif
