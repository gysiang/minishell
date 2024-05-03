#include "../includes/minishell.h"

static void signal_free(t_shell *minishell)
{
    if (minishell) // Check if minishell pointer is not NULL
        free_and_exit(minishell, 130); // Call free_and_exit function with minishel pointer and exit status 130
}

static void signal_exit(int signal_number)
{
    (void)signal_number; // Cast signal_number to void suppress unused parameter warning
    printf("\n"); // Print a newline character
    signal_free(NULL); // Call signal_free function with NULL pointer
}

static void error_EOF(char *end_of_file)
{
    // Print error message indicating here-doc was dleimited byt end-of -file
    ft_putstr_fd("minishell: warning: here_document delimited by end-of-file (wanted ", 2);
    ft_putstr_fd(end_of_file, 2); // Print the expected delimiter
    ft_putendl_fd(")", 2); // Print closing parenthesis and newline
}

static void here_doc_read(t_shell * minishell, int *pipe_fds, char *delimiter)
{
    char *str;
    size_t  delimiter_len;

    delimiter_len = ft_strlen(delimiter); // Calculate the length of the delimirter
    close(pipe_fds[0]); // Close the read end of the pipe
    signal_free(minishell); // Call signal_free function with minishell pointer
    signal(SIGINT, signal_exit); // Set the signal handler for SIGINT to signal_exit function
    while (1) // Start an infinite loop
    {
        str = readline("> "); // Read input from the user with a prompt "> "
        if (!str) // Check if str is NULL (indicating end-of-file)
        {
            error_EOF(delimiter); // Call error_EOF function with the delimiter
            break; // Break out of the loop
        }
        if (ft_strncmp(str, delimiter, delimiter_len + 1)) // Compare the input str with the dleimiter
        {
            free(str); // If the input matches the delimiter, free str and break otu of the loops
            break;
        }
        write(pipe_fds[1], str, ft_strlen(str)); // Write the input str to thr write end of the pipe
        write(pipe_fds[1], "\n", 1); // Write a newline character to thr write end of the pipe
        free(str); // Free the str variable
    }
    close(pipe_fds[1]); // Close the write end of the pipe
    free_and_exit(minishell, 0); // Call free_and_exit function with minishell pointer and exit status 0
}


int here_doc(t_shell *minishell, char *delimiter)
{
    int pipe_des[2];
    int status;
    int pid;

    pipe(pipe_des); // Create a pipe and store the file descriptoer in pipre_des array
    pid = fork(); // Fork a child process
    if (pid == 0)// If in the child process (pid is 0)
    {
        here_doc_read(minishell, pipe_des, delimiter); // Call here_doc_read function with minshell, pipe_des and dleimiter
        exit(0);
    }
    waitpid(pid, &status, WUNTRACED); // Wait for the child process to finish and sotre the status
    if (WEXITSTATUS(status) == 130) // If the child status is 130
    {
        close(pipe_des[0]); // Close the read end of the pipe
        pipe_des[0] = -1; // Set read end to -1 , indicating an error
    }
    close(pipe_des[1]); // Close the write end of the pipe
    return (pipe_des[0]); // Return the read end of the pipe
}
