# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mskinner <v.golskiy@ya.ru>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/28 01:17:41 by mskinner          #+#    #+#              #
#    Updated: 2020/11/13 18:17:41 by mskinner         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc

BINDIR = .
BUILDDIR = ./build
INCLUDEDIR = ./include
SOURCEDIR = ./src
LIBFT = ./libft

CFLAGS = -Wall -Wextra -Werror

SOURCE_FILES =	assert.c                builtin_pwd.c           expander_impl.c         hash_core.c             lexer.c                 parser_operations.c \
				builtin.c               builtin_unset.c         expander_impl_2.c       hash_extra.c            lexer_actions_1.c       parser_token_creators.c \
				builtin_cd.c            common.c                expander_inner.c        hash_internal.c         lexer_actions_2.c       prompt.c \
				builtin_declare.c       common_io.c             expander_outer.c        hash_to_envp.c          lexer_actions_3.c       repl.c \
				builtin_echo.c          common_lists.c          functions_fork.c        ipc_forwarding.c        lexer_predicates.c      resolve_path.c \
				builtin_env.c           envp_to_hash.c          get_next_line.c         ipc_piping.c            main.c                  shell_features.c \
				builtin_exit.c          expander.c              handle_path.c           ipc_piping_testing.c    parser.c                signals.c \
				builtin_export.c        expander_helpers.c      hash.c                  ipc_piping_waiting.c    parser_children.c
HEADER_FILES =	common.h        envp.h          executor.h      get_next_line.h hash.h          lexer.h         minishell.h     parser.h

OBJ = $(SOURCE_FILES:%.c=$(BUILDDIR)/%.o)
HRD = $(HEADER_FILES:%.h=$(INCLUDEDIR)/%.h)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c ${HRD}
	@mkdir -p ${BUILDDIR}
	@$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@

$(BINDIR)/$(NAME): ${OBJ} ${HRD}
	@$(MAKE) -C $(LIBFT) bonus
	@mkdir -p ${BINDIR}
	@$(CC) $(CFLAGS) $(OBJ) -L\libft -lft -o $(BINDIR)/$(NAME)

all: $(BINDIR)/$(NAME)
	
clean:
	@rm -rf ${BUILDDIR}
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(BINDIR)/$(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
