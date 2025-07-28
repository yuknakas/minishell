# Minishell — Project Overview

## Description
This project is a custom implementation of a simple command-line shell in C. The project is in an early stage: the main structures, function stubs, and a custom standard library (libft) are in place, with initial work on tokenization and command path search.

---

## Project Structure

```
min/
├── README.md                # Project overview and structure
├── Makefile                 # Build script for minishell and libft
├── main.c                   # Entry point, shell_loop stub
├── a.out                    # Compiled binary (temporary)
├── test.c                   # (Possibly for tests)
│
├── include/                 # Project header files
│   ├── minishell.h          # Main declarations, includes, functions
│   └── structs.h            # All data structures (tokens, commands, env, etc.)
│
├── src/                     # Core minishell logic
│   ├── main.c               # Shell entry point
│   ├── exec/                # Command search and execution
│   │   ├── absolute_path.c
│   │   └── find_path.c
│   ├── token/               # Command line tokenization
│   │   ├── token.c
│   │   ├── tokenize.c
│   │   ├── ft_strndup.c
│   │   ├── iskey.c
│   ├── signal/              # Signal handling
│   │   └── signals_func.c
│   ├── pipex/               # (Empty) Placeholder for pipes
│   └── utils/               # Utilities and helpers
│       ├── 01_readline.c    # User input reading
│       └── 10_errors.c      # Error handling
│
├── libft/                   # Custom standard library implementation (all string, memory, list, gnl, ctype, etc. functions are here)
│
├── subjects/                # Documentation and guides
│   ├── en.subject.pdf
│   └── guids
│
├── .vscode/                 # Editor settings
│   └── settings.json
│
└── .git/                    # Git repository (service folder)
```

---

## Module Overview
- **src/main.c** — Shell entry point, currently only prints env and has a shell_loop stub.
- **include/** — All structures and function declarations.
- **src/token/** — Command line tokenization and helpers.
- **src/exec/** — Command path search and preparation for execution.
- **src/utils/** — Utilities and helpers (input reading, error handling).
- **src/signal/** — Signal handling (e.g., Ctrl+C).
- **src/pipex/** — Currently empty, placeholder for pipes.
- **libft/** — Custom implementation of standard C library functions (strings, memory, lists, gnl, etc.).
- **subjects/** — Project documentation.

---

## What is implemented
- Project structure and main directories
- All main data structures (tokens, commands, env, redirections)
- Initial tokenization logic (splitting input into tokens)
- Initial command path search logic (find_path, absolute_path)
- libft library (strings, memory, lists, gnl, etc.)
- Stubs for error and signal handling

## What is NOT implemented
- Main shell loop (shell_loop) — only a stub
- Command execution (execute) — only declarations
- Support for pipes, redirections, environment variables — only structures and stubs
- Full parser and user input handling
- Real-time user interaction (parsing, command execution, error handling)

---

## How to read the project
- For data structures — see `include/structs.h`
- For function declarations and entry points — `include/minishell.h` and `src/main.c`
- For tokenization — `src/token/`
- For command path search — `src/exec/`
- For errors — `src/utils/10_errors.c`
- For signals — `src/signal/signals_func.c`
- For standard functions — `libft/`

---

## Documentation
- Main subject: `subjects/en.subject.pdf`
- Guides and notes: `subjects/guids`

---

> **Project is under development.**
> If you are new here, this file will give you a quick understanding of what is implemented and where to find the code. 