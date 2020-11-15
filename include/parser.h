/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:59:34 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 18:36:43 by mskinner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./common.h"
# include "./hash.h"
# include "./lexer.h"

enum	e_token_type
{
	ROOT = 1,
	PART = 2,
	EXEC = 3,
	IO = 4,
	WORD = 5,
};

typedef struct			s_token
{
	enum e_token_type	type;
	int					start;
	int					stop;
	struct s_token		**child;
	t_lexer				*context;
}						t_token;

t_token					*create_token(t_lexer *context,
						enum e_token_type type, int start, int stop);
t_token					*create_word(t_token *part, int start);
t_token					*create_exec(t_token *parent, int start);
t_token					*create_part(t_token *root, int start);
t_token					*create_root(t_lexer *context);
t_token					*create_child(t_token *parent, int start);
void					destory_tree(t_token *token);
void					create_childen(t_token *parent);
void					print_root(t_token *token);

char					**get_resolution_paths(t_hash *root);

int						skip_while_category_is(t_token *t, char c, int i);
int						skip_until_category_is(t_token *t, char c, int i);
int						skip_while_category_matches(t_token *t,
						t_boolean matcher(char c), int i);
int						skip_until_category_matches(t_token *t,
						t_boolean matcher(char c), int i);

t_boolean				is_text_cat(char c);
t_boolean				is_quote(char c);
t_boolean				is_redirection(char c);
t_boolean				is_special(char c);

char					*get_next_space(char *c);
t_boolean				has_child(t_hash *node, char letter);
char					*temp_string(int size);
char					*concat_string_filtering_empty(t_lst *list);

#endif
