#include "../inc/parser.h"

//////////////////////////////////
// MAIN LOOP
//////////////////////////////////

int main(void)
{
	char *input;
	t_pipes *pipeline, *curr;
	size_t n_pipes;

	printf("===== MINISHELL PARSER INTEGRATED =====\n");

	while (1)
	{
		input = readline("minishell>> ");
		if (!input || strcmp(input, "exit") == 0)
			break;
		if (strlen(input) == 0)
		{
			free(input);
			continue;
		}

		add_history(input);
		char **split = ft_split(input, '|', &n_pipes);

		pipeline = NULL;
		for (size_t i = 0; i < n_pipes; i++)
		{
			t_pipes *new_node = malloc(sizeof(t_pipes));
			if (!new_node)
				break;
			new_node->str = strdup(split[i]);
			new_node->index = i;
			new_node->next = pipeline;
			pipeline = new_node;
		}

		curr = pipeline;
		while (curr)
		{
			printf("PIPE [%zu]: %s\n", curr->index, curr->str);
			t_tokens *tokens = check_args(curr->str);
			print_tokens(tokens);
			free_tokens(tokens);
			curr = curr->next;
		}

		// Cleanup
		free_pipes(pipeline);
		for (size_t i = 0; i < n_pipes; i++)
			free(split[i]);
		free(split);
		free(input);
	}

	printf("========= THE END MINISHELL =========\n");
	return 0;
}
