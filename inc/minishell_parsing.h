/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlorenzo <vlorenzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:21:52 by dalabrad          #+#    #+#             */
/*   Updated: 2025/06/29 11:27:16 by vlorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

//////////////////////////////////
// HEADERS FROM INCLUDED LIBRARIES
//////////////////////////////////

# include "array_utils.h"
# include "libft.h"
# include "minishell_exec.h"
# include "minishell_signals.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//////////////////////////////////
//-----MINISHELL PROMTP----------
//////////////////////////////////

# define PROMPT "minishell>>"

//////////////////////////////////
//-----STRUCTURES----------------
//////////////////////////////////

typedef struct s_cmd	t_cmd;
typedef struct s_data	t_data;
typedef struct s_tokens	t_tokens;
typedef struct s_env	t_env;

// ENUM TOKENS STRUCT
typedef enum t_TokenType
{
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND_OUT,
	OPTION,
	COMMAND,
	SETTING,
	PATH,
	ARG,
	ERROR
}						t_TokenType;
// PIPES
typedef struct s_pipes // pipes
{
	char *str;
	size_t index;
	struct s_pipes *next;
}						t_pipes;

// TOKENS

struct					s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_TokenType			type;
	t_tokens			*next;
};

// comms
typedef struct s_comms
{
	/* t_env				*env; */
	t_tokens			*token;
	int					i;
	struct s_comms		*next;
}						t_comms;

// MINI-SPLIT STRUCT
typedef struct s_split
{
	char				**split;
	const char			*s;
	char				c;
}						t_split;

//////////////////////////////////
//-----FUNCTIONS-----------------
//////////////////////////////////

// UTILS INIT & HANDLE
int						handle_token_alloc_fail(char **segments, char *line);
t_pipes					*init_struct(t_pipes *args);
int						init_pipe_segments(char *line, char ***segments,
							size_t *n);
t_tokens				**init_tokens_by_segment(size_t count);

// UTILS CLEAN STRUCTS

t_pipes					*clean_struct(t_pipes *args);
void					free_tokens_list(t_tokens *head);
int						is_exit_command(char *line);
void					cleanup(char *line, char **segments, t_tokens **tokens,
							size_t n);

// FT-MINI-SPLIT
size_t					splitted_len(const char *s, char c);
char					**split2array(const char *s, char c, char **array,
							size_t w_count);
char					**ft_minisplit(const char *s, char c, size_t *n);
size_t					count_splitted(const char *s, char c);

// UTILS PARSING
int						is_path(const char *str);
int						is_path(const char *str);
void					print_tokens(t_tokens *list);
int						ft_lstadd_front2(t_pipes **lst, t_pipes *new);
int						ft_lstadd_front2(t_pipes **lst, t_pipes *new);
const char				*skip_space(const char *s);
size_t					is_open(const char *s);

// FT_CLASIFY TOKENS
t_TokenType				clasify_token(const char *str);
void					set_command_type(t_tokens *tokens);
const char				*token_type_str(t_TokenType type);
char					*poly_substr(const char *s, size_t *i, int *was_quoted);
t_tokens				*check_args_fixed(const char *input, size_t *i_words);

// PROCESS BY SEGMENT OR PIPE
void					process_single_segment(char *segment,
							t_tokens **token_ptr, t_cmd **cmd_ptr,
							size_t index);
void					process_segments(char **segments, t_tokens **tokens,
							size_t n, t_data *data);

// TOK_TO_CMD
t_cmd					*tokens_to_cmd(t_tokens *tokens);
int						is_invalid_redirection_sequence(t_tokens *token);

// EXPAND & FOR EXEC
char					*get_env_value_from_list(const char *name, t_env *env);
char					*expand_variables(const char *str, t_env *env,
							int was_quoted, int last_status);
void 					expand_tokens(t_tokens *tokens, t_env *env, int last_status);
#endif