# Minishell-bash

Minishell-bash is an open-source project aimed at creating a minimal shell that replicates some of the basic functionalities of the famous Unix shell, Bash. This project is designed to be a learning tool to understand how command line interpreters work in Unix-like systems.

## Features

- **Command Execution:** Executes general commands available in the Unix environment.
- **Built-in Commands:** Includes `cd`, `pwd`, `echo`, and `exit`.
- **Environment Variables:** Supports setting and using environment variables.
- **Pipes and Redirections:** Implements basic pipes (`|`) and redirections (`>`, `<`, `>>`).
- **Signal Handling:** Handles `CTRL+C`, `CTRL+D`, and `CTRL+\` to mimic the behavior seen in more complex shells.

## Installation

To get started with Minishell-bash, clone this repository to your local machine by running:

```bash
git clone https://github.com/turman17/Minishell-bash.git
cd Minishell-bash
```

### Requirements

- GCC compiler
- Make
- Linux environment

### Compiling the project

Compile the project using:

```bash
make
```

This will create the executable named `minishell`.

## Usage

Run the shell by executing:

```bash
./minishell
```

Once running, you can execute commands as you would in any other shell.

### Complex Command Examples

1. **Advanced Pipe Usage:**
   Filter and sort error messages from a log file:
   ```bash
   cat /var/log/syslog | grep 'error' | sort | uniq -c | sort -nr
   ```

2. **Handling Multiple Redirections and File Descriptors:**
   Compile a program, handling output and errors separately:
   ```bash
   gcc main.c -o main.out 2>errors.log >compile.log
   ```

3. **Complex Command with Subshells and Variable Expansion:**
   Count backup files created today:
   ```bash
   echo "Backup files count: $(ls -l backup_$(date +%Y%m%d)*.tar.gz | wc -l)"
   ```
