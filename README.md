# Parser: Minishell-Vanessa's Fork/branch:test

Minishell parsing logic with an interactive CLI and unit test support.

---

## FEATURES

- Pipe parsing (`|`)
- Tokenization (`echo`, `"text"`, `>`, `<`, etc.)
- Redirection handling
- Argument parsing (`""`, `''`, etc.)


## USE:

>> make
>> ./parser
>> minishell>> write you arguments
>> PRESS Ctrl + C to eXIT

## TESTS:

>> make clean
>> make test
>> ./test_parser

## STRUCTURE:Minishell-Vanessa's Fork/branch:test
```
│
├── Makefile
├── include/
│   └── parser.h            # Header file for parsing logic
│
├── src/
│   ├── parser.c            # Core parsing logic
│   └── main.c              # Interactive shell loop
│
├── tests/
│   └── test_parser.c       # Unit tests
´´´