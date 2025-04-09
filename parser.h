#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdbool.h>

typedef struct s_pipes
{
	char *str;
	size_t index;
	struct s_pipes *next;
}	t_pipes;

typedef struct s_tokens
{
	int					was_quoted;
	int					skip;
	char				*str;
	struct s_tokens		*next;
}	t_tokens;

// PARSING
t_tokens	*check_args(const char *str);
char		*poly_substr(const char *s, size_t *i);
void		print_tokens(t_tokens *token);
void		free_tokens(t_tokens *token);
void		free_pipes(t_pipes *pipes);

// UTILS
char		*ft_substr(const char *s, unsigned int start, size_t len);
const char	*skip_space(const char *s);
char		**ft_split(const char *s, char c, size_t *n);
size_t		count_splitted(const char *s, char c);

#endif
