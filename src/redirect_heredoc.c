#include "minishell.h"

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

    printf("in heredoc read\n");
    delimiter_len = ft_strlen(delimiter);
    close(pipe_fds[0]);
    signal_free(minishell);
    signal(SIGINT, signal_exit);
    while (1)
    {
        printf("bfore triggered readline\n");
        str = readline("> ");
        printf("triggered readline\n");
        if (!str)
        {
            error_EOF(delimiter);
        }
        if (!ft_strncmp(str, delimiter, delimiter_len + 1))
        {
            free(str);
        }
        if (write(pipe_fds[1], str, ft_strlen(str)) == -1)
            exit(EXIT_FAILURE);
        if (write(pipe_fds[1], "\n", 1))
             exit(EXIT_FAILURE);
        free(str);
    }
    close(pipe_fds[1]);
    free_and_exit(minishell, 0);
}


int here_doc(t_shell *minishell, char *delimiter)
{
    int pipe_des[2];
    int status;
    int pid;

    if (pipe(pipe_des) == -1)
        exit(EXIT_FAILURE);
    pid = fork();
    printf("forked heredoc\n");
    if (pid == 0)
    {
        here_doc_read(minishell, pipe_des, delimiter);
        exit(0);
    }
    waitpid(pid, &status, WUNTRACED);
    if (WEXITSTATUS(status) == 130)
    {
        close(pipe_des[0]);
        pipe_des[0] = -1;
    }
    close(pipe_des[1]);
    return (pipe_des[0]);
}
