/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:32:33 by dchief            #+#    #+#             */
/*   Updated: 2020/11/10 17:31:35 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdarg.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "get_next_line.h"

typedef enum			e_bool
{
	false = 0,
	true = 1
}						t_boolean;

typedef struct			s_listelem
{
	void				*value;
	struct s_listelem	*next;
}						t_listelement;

typedef struct			s_lists
{
	int					count;
	t_listelement		*first;
	t_listelement		*last;
}						t_lst;

t_lst					*init_list(void);
int						push_to_list(t_lst *list, void *value);
void					**to_array(t_lst *list);
char					*concat_string(t_lst *list, t_boolean autofree);
char					*joinstring(char *a, char sep, char *b);
int						push_to_list2(t_lst *list, void *v1, void *v2);
int						push_to_list3(t_lst *list, void *v1,
						void *v2, void *v3);
void					assert(t_boolean ok, char *context,
							char *message, int code);
char					*safe_clone(char *start, char *stop);
#endif
