# Minishell

Minishell is a simplified Unix shell implemented in C as part of the 42 curriculum.  
It replicates basic shell behavior by interpreting user input and executing commands in an interactive terminal session.

## Features

- Prompt display and command input loop
- Execution of built-in and external commands
- Argument parsing and tokenization
- Handling of quotes, pipes (`|`), redirections (`<`, `>`, `>>`, `<<`)
- Environment variable expansion (`$VAR`)
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Signal handling (e.g., `Ctrl+C`, `Ctrl+\`)
- Exit status management
- Memory management and cleanup

## Purpose

This project deepened understanding of process management, file descriptors, parsing, and signal handling in a Unix-like environment.  
It also emphasized writing modular, maintainable C code under strict constraints (no use of system functions like `printf`, `malloc`, etc. outside the allowed ones).
