# Test Minishel – Parser Interactivo

Este proyecto es una herramienta para testear y visualizar cómo un minishell puede analizar comandos ingresados por el usuario. Ideal para debugging de:

- Pipes (`|`)
- Tokens (`echo`, `"text"`, `>`, `<`, etc.)
- Redirecciones

## Uso

```bash
make
./parser

minishell-tools/
├── Makefile
├── include/
│   └── minishell_parser.h
├── src/
│   ├── minishell_parser.c
│   └── test.c

