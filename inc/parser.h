#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND_OUT,
	TOKEN_HEREDOC,
	TOKEN_PIPE
} t_token_type;

typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	t_token_type		type;
	struct s_tokens		*next;
}	t_tokens;


typedef struct s_pipes
{
	char *str;
	size_t index;
	struct s_pipes *next;
}	t_pipes;

// PARSING
t_tokens	*check_args(const char *str);
char		*poly_substr(const char *s, size_t *i);
static void	print_tokens(t_tokens *token);
void		free_tokens(t_tokens *token);
void		free_pipes(t_pipes *pipes);
t_tokens 	*check_args_fixed(const char *input);

// UTILS
char		*ft_substr(const char *s, unsigned int start, size_t len);
const char	*skip_space(const char *s);
char		**ft_split(const char *s, char c, size_t *n);
size_t		count_splitted(const char *s, char c);

// TEST

void 		run_parser_tests(void);
static void print_tokens(t_tokens *token);


#endif
