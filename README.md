# Minishell

A simple shell implementation in C, built as part of the 42 curriculum.

## Authors

- Paulo Sérgio
- João Cavadas

## About

Minishell recreates the behavior of a basic Unix shell, handling command execution, pipes, redirections, environment variables, signals, and built-in commands — closely following the behavior of **bash**.

## Features

- **Interactive prompt** with command history (via `readline`)
- **Command execution** using `fork` / `execve`
- **Pipes** — chain commands with `|`
- **Redirections** — `<`, `>`, `>>`, and `<<` (heredoc)
- **Environment variables** — expansion with `$VAR` and `$?`
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave as in bash
- **Quoting** — single quotes `'` and double quotes `"` handled correctly

## Built-ins

The following commands are implemented natively (without forking):

| Command | Description |
|---------|-------------|
| `echo` | Print text, supports `-n` flag |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Print all environment variables |
| `exit` | Exit the shell |

## Usage
```bash
make
./minishell
```

> Does not accept additional arguments.

## Requirements

- GCC
- GNU Make
- `readline` library

## Parsing

The parser processes raw input character by character before any execution takes place. It handles:

- **Tokenization** — the input string is split into tokens (commands, arguments, operators) respecting spaces and shell metacharacters
- **Quote handling** — single quotes disable all expansion; double quotes allow `$VAR` expansion but suppress most special characters. Empty quotes (`''`, `""`) produce an empty token. Unclosed quotes produce a syntax error
- **Environment variable expansion** — `$VAR` is expanded inline during tokenization, including inside double quotes. Expansion can be selectively disabled (e.g. after a `\` or inside single quotes)
- **Operator detection** — `|`, `>`, `>>`, `<`, and `<<` are identified and tokenized separately from arguments
- **Syntax error checking** — malformed operator sequences are caught before execution, such as `|` at the start, `||`, or a redirection with no valid target. These set `exit_status = 2` and halt processing
- **Ambiguous redirections** — if a `$VAR` used as a redirect target expands to empty or multiple words, an ambiguous redirect error is raised
- **Heredoc** — `<<` sets a flag to disable expansion of the delimiter and handles EOF quoting correctly

## Project Structure
```
minishell/
├── include/        # Header files
├── src/            # Source files
│   ├── minishell.c # Entry point
│   ├── exec.c      # Command execution
│   ├── pipes.c     # Pipe handling
│   ├── parser_handler.c
│   ├── signal_functions.c
│   └── ...
├── Libft/          # Custom C library
└── Makefile
```

## Notes

- The only global variable used is `g_exit_code`, to capture signal-based exit codes.
- Built-ins are executed in the parent process to correctly affect shell state (e.g. `cd`, `export`).
