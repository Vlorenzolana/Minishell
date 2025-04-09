#include "../inc/parser.h"

// Basic unit test
void run_parser_tests(void)
{
	const char *tests[] = {
		"echo hello world",
		"ls -la | grep .c",
		"cat < file.txt | sort > output.txt",
		"cat < 'file.txt | sort > output.txt",
		NULL};

	for (int i = 0; tests[i] != NULL; i++)
	{
		printf("Test %d: %s\n", i + 1, tests[i]);
		t_tokens *tokens = check_args_fixed(tests[i]);
		print_tokens(tokens);
		// Add code here to free tokens if needed
		printf("\n");
	}
}

int main(void)
{
	printf("Running parser tests...\n\n");
	run_parser_tests();
	printf("All tests done.\n");
	return 0;
}
