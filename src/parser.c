#include "../inc/parser.h"

t_token_type classify_token(const char *str)
{
	if (!str)
		return TOKEN_WORD;
	if (strcmp(str, "<") == 0)
		return TOKEN_REDIRECT_IN;
	if (strcmp(str, ">") == 0)
		return TOKEN_REDIRECT_OUT;
	if (strcmp(str, ">>") == 0)
		return TOKEN_APPEND_OUT;
	if (strcmp(str, "<<") == 0)
		return TOKEN_HEREDOC;
	if (strcmp(str, "|") == 0)
		return TOKEN_PIPE;
	return TOKEN_WORD;
}

 char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	if (!s || start >= strlen(s))
		return strdup("");
	if (start + len > strlen(s))
		len = strlen(s) - start;
	char *sub = malloc(len + 1);
	if (!sub)
		return NULL;
	memcpy(sub, s + start, len);
	sub[len] = '\0';
	return sub;
}

const char	*skip_space(const char *s)
{
	while (*s == ' ' && *s != 0)
		s++;
	return (s);
}

char	*poly_substr(const char *s, size_t *i)
{
	size_t	init = *i;
	bool	is_single = false;
	bool	is_double = false;

	s = skip_space(s);
	init = *i;

	while (s[*i] != '\0')
	{
		if (s[*i] == '"' && !is_single)
			is_double = !is_double;
		else if (s[*i] == '\'' && !is_double)
			is_single = !is_single;
		else if (s[*i] == ' ' && !is_single && !is_double)
			break;
		(*i)++;
	}
	return ft_substr(s, init, *i - init);
}

size_t	count_splitted(const char *s, char c)
{
	size_t	count = 0;
	size_t	i = 0;

	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return count;
}

char	**ft_split(const char *s, char c, size_t *n)
{
	size_t	i = 0, j = 0, k = 0;
	*n = count_splitted(s, c);
	char **res = malloc(sizeof(char *) * (*n + 1));
	if (!res)
		return NULL;

	while (j < *n)
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
			i++;
		res[j++] = ft_substr(s, k, i - k);
	}
	res[j] = NULL;
	return res;
}

//////////////////////////////////
// PARSING
//////////////////////////////////

t_tokens	*check_args_fixed(const char *str)
{
	t_tokens	*head = NULL, *curr = NULL;
	size_t		i = 0;

	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break;

		t_tokens *new_tok = malloc(sizeof(t_tokens));
		if (!new_tok)
			break;
		new_tok->str = poly_substr(str, &i);
		new_tok->type = classify_token(new_tok->str);
		new_tok->next = NULL;
		new_tok->skip = 0;
		new_tok->was_quoted = 0;

		if (!head)
			head = new_tok;
		else
			curr->next = new_tok;
		curr = new_tok;
	}
	return head;
}

void	print_tokens(t_tokens *token)
{
	int i = 0;
	while (token)
	{
		printf("  TOKEN[%d]: \"%s\"\n", i++, token->str);
		token = token->next;
	}
}

void	free_tokens(t_tokens *token)
{
	t_tokens *tmp;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_pipes(t_pipes *pipes)
{
	t_pipes *tmp;
	while (pipes)
	{
		tmp = pipes;
		pipes = pipes->next;
		free(tmp->str);
		free(tmp);
	}
}
