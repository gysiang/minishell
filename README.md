# Minishell Overview

Objective: Create a simplified bash shell with specific functionalities.

Functionalities: Command prompt display, command history, executables handling, quote recognition, redirections, pipes, environment variables, signal handling, and a set of built-in commands.

## To see how commands are executed in bash
bash -x -c 'cat minishell.h | grep ");"$'

#### Valgrind Supression Command

valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell


## Pseudo Code Structure
### Initialization

- [x] Set up the environment (e.g., copy environment variables).
- [x] Initialize signal handling for ctrl-C (SIGINT) and ctrl-D (EOF).
- [x] Main Loop
- [x] Display a prompt.
- [x] Read input from the user.
- [x] If input is empty or only spaces, continue to the next iteration.
- [x] Add input to history.
- [ ] Check and handle input errors.
- [x] Parse and route the command.
- [x]Clear up command list for next input.
- [x] Repeat unless an exit condition is met (e.g., "exit" command or ctrl-D).

### Command Parsing and Execution

- [x] Lexer (Tokenizer): Breaks down input into tokens (words or symbols).
- [] Parser: Groups tokens into commands and their arguments, identifying redirections, pipes, and built-in commands.
- [x] Executor: Executes the commands based on parsed data.
- [x]For built-in commands (like cd, exit), execute directly in the shell.
- [x] For external commands, find the executable and run it, handling input/output redirection and piping as needed.
- [x]Built-in Commands Handling

Identify if the first word of a command is a built-in command.
If so, execute the corresponding function directly within the shell.

### Redirections and Pipes

- [x] Handle input (<), output (>), append (>>), and heredoc (<<) redirections by adjusting file descriptors.
- [x] Use pipes (|) to connect the output of one command to the input of another.

### Environment Variables and Exit Status

- [ ] Replace $VARIABLE with its value.
- [ ] Replace $? with the last command's exit status.
- [x] Signal Handling

- [x] Ensure ctrl-C, ctrl-D, and ctrl-\ are handled similarly to bash.
- [x] Reset and Cleanup

After each command execution or on exit, free allocated resources and prepare for the next input or shutdown.

**Simplified Explanation**

The minishell starts by setting up its environment and handling signals.
It then enters a loop where it displays a prompt, awaits user input, and processes that input.
Input processing involves breaking the input into parts (lexer), organizing these parts into commands and their parameters (parser), and then executing these commands (executor).
Special handling is provided for built-in commands, redirections, pipes, and environment variables.
The shell also handles signals (like ctrl-C) in a manner similar to bash.
After executing the commands, the shell cleans up any used resources and is ready for the next input or to exit if instructed.
