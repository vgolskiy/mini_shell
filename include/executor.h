/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchief <dchief@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:19:53 by mskinner          #+#    #+#             */
/*   Updated: 2020/11/15 19:51:36 by dchief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../libft/libft.h"
# include "parser.h"
# include "minishell.h"
# include <string.h>

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

/*
** path - working directory
** pid - last executed command identification number
*/

typedef struct		s_resolved
{
	char			**argv;
	char			**fwd;
	char			**envp;
	int				argc;
}					t_resolved;

typedef struct		s_ex
{
	char			path[PATH_MAX];
	char			*user;

	t_token			*root;
	t_token			*pipeline;
	t_token			*command;

	t_resolved		process;
	t_mini_shell	*shell;
}					t_ex;

struct				s_resolution_context {
	t_ex			*ex;
	t_lst			*list;
	t_lst			*list_sec;
	t_token			*t;
	char			*tmp;
	char			*cur;
	int				i;
};

typedef struct		s_builtin_cmd
{
	char			*name;
	int				(*fn)(t_ex *ex);
}					t_builtin_cmd;

t_builtin_cmd		get_builtin_by_name(char *cmd);
char				*getprompt(t_ex *ex);

/*
** FUNCTIONS BUILTIN 1 & 2
*/
int					ft_pwd(t_ex *ex);
int					ft_echo(t_ex *ex);
int					ft_env(t_ex *ex);
int					ft_print_export(void);
int					ft_exit(t_ex *ex);
int					ft_unset(t_ex *ex);
int					ft_cd(t_ex *ex);
int					ft_declare(t_ex *ex);
int					ft_export(t_ex *ex);

/*
** FORKING & PIPING
*/
int					handle_fork(char *cmd, t_ex *ex);
void				setup_input_pipe_fd(t_token *pipeline, t_token *command,
						int *pipefd, t_ex *ex);
void				setup_output_pipe_fd(t_token *pipeline,
							t_token *command, int *pipefd, t_ex *ex);

void				env_fd(t_hash *root, int fd);
void				process_forward(char *line);
void				process_command(t_token *t, t_ex *ex);
void				process_pipeline(t_token *t, t_ex *ex);
t_boolean			repl(t_ex *ex);
t_ex				*init_ex(void);
void				setup_shell_level(t_ex *ex);
void				setup_global_ex(t_ex *ex);
void				reset_signal(void);
void				handle_signal(void);

char				*create_executable(char *path, char *cmd);
char				*resolve_fullpath(char *cmd);
char				*check_file_exists(char *cmd);

void				kill_all_pipeline(t_ex *ex);
void				print_err(char *msg1, char *variable, char *msg2);

void				*resolve_argument(t_token *t,
					t_ex *ex, t_lst *list);
void				resolve_environ_value(struct s_resolution_context *ctx);
void				resolve_environ_value_outer(struct s_resolution_context
					*ctx);
t_resolved			resolve_arguments_redirects(t_token *p, t_ex *ex);
void				resolve_argument_impl(struct s_resolution_context *ctx);
void				resolve_argument_impl_cat_dollar(struct
						s_resolution_context *ctx);
void				resolve_argument_impl_cat_exclaim(struct
						s_resolution_context *ctx);
void				resolve_argument_impl_cat_at(struct
						s_resolution_context *ctx);
void				resolve_argument_impl_cat_default(struct
						s_resolution_context *ctx);
void				resolve_argument_impl_ensure_temp_string(struct
						s_resolution_context *ctx);
void				resolve_argument_impl_flush_temp_string(struct
						s_resolution_context *ctx);
void				test_syntax_pipeline(t_token *t, t_ex *ex);
void				wait_for_all_cmds(t_ex *ex);
void				cheanup_ex(t_ex *ex);
void				wait_for_pipeline(pid_t pid, t_ex *ex);
void				hash_import(t_hash *root, char *envp, t_boolean force);
void				setup_shell_pwd(t_ex *ex);
void				lexer_destroy(t_lexer *my);
char				*linegetter(char *prompt, t_ex *ex);
t_boolean			ft_isatty(int fd);
t_boolean			ft_isafile(int fd);

#endif
