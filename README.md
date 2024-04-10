Minishell Overview
Objective: Create a simplified bash shell with specific functionalities.
Functionalities: Command prompt display, command history, executables handling, quote recognition, redirections, pipes, environment variables, signal handling, and a set of built-in commands.
Pseudo Code Structure
Initialization

Set up the environment (e.g., copy environment variables).
Initialize signal handling for ctrl-C (SIGINT) and ctrl-D (EOF).
Main Loop

Display a prompt.
Read input from the user.
If input is empty or only spaces, continue to the next iteration.
Add input to history.
Check and handle input errors.
Parse and route the command.
Clear up command list for next input.
Repeat unless an exit condition is met (e.g., "exit" command or ctrl-D).
Command Parsing and Execution

Lexer (Tokenizer): Breaks down input into tokens (words or symbols).
Parser: Groups tokens into commands and their arguments, identifying redirections, pipes, and built-in commands.
Executor: Executes the commands based on parsed data.
For built-in commands (like cd, exit), execute directly in the shell.
For external commands, find the executable and run it, handling input/output redirection and piping as needed.
Built-in Commands Handling

Identify if the first word of a command is a built-in command.
If so, execute the corresponding function directly within the shell.
Redirections and Pipes

Handle input (<), output (>), append (>>), and heredoc (<<) redirections by adjusting file descriptors.
Use pipes (|) to connect the output of one command to the input of another.
Environment Variables and Exit Status

Replace $VARIABLE with its value.
Replace $? with the last command's exit status.
Signal Handling

Ensure ctrl-C, ctrl-D, and ctrl-\ are handled similarly to bash.
Reset and Cleanup

After each command execution or on exit, free allocated resources and prepare for the next input or shutdown.
Simplified Explanation
The minishell starts by setting up its environment and handling signals.
It then enters a loop where it displays a prompt, awaits user input, and processes that input.
Input processing involves breaking the input into parts (lexer), organizing these parts into commands and their parameters (parser), and then executing these commands (executor).
Special handling is provided for built-in commands, redirections, pipes, and environment variables.
The shell also handles signals (like ctrl-C) in a manner similar to bash.
After executing the commands, the shell cleans up any used resources and is ready for the next input or to exit if instructed.
