# Parser & Test Interactivo

Minishel parsing and testing.

- Pipes (`|`)
- Tokens (`echo`, `"text"`, `>`, `<`, etc.)
- Redirections

## USE:

>> make
>> ./parser
>> minishell>> write you arguments
>> PRESS Ctrl + C to eXIT

## TESTS:

>> make clean
>> make test
>> ./test_parser

## STRUCTURE:
Minishell/
│
├── Makefile
├── include/
│   └── parser.h
│
├── src/
│   ├── parser.c      # Parsing logic
│   └── main.c        # Your interactive shell loop (moved from parser.c)
│
├── tests/
│   └── test_parser.c # Unit tests

