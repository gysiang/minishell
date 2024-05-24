/*void execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
    int pipe_fd[2];
    int pid;
    int status;

    printf("Executing command index: %d\n", i);

    if (!last_command)
    {
        if (pipe(pipe_fd) == -1) {
            perror("Failed to create pipe");
            exit(EXIT_FAILURE);
        }
        printf("Pipe created: read fd = %d, write fd = %d\n", pipe_fd[0], pipe_fd[1]);
    }

    pid = fork();
    printf("Fork result: %d\n", pid);

    if (pid == 0) // Child process
    {
        if (i != 0)
        {
            dup2(minishell->ret_fd[0], STDIN_FILENO);
            close(minishell->ret_fd[0]);
        }
        if (!last_command)
        {
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
        }
        exec_cmd(curr->token, minishell);
        exit(EXIT_FAILURE);
    }
    else // Parent process
    {
        if (!last_command)
        {
            close(pipe_fd[1]);
            minishell->ret_fd[0] = pipe_fd[0];
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            minishell->last_return = WEXITSTATUS(status);
        }
        else
        {
            minishell->last_return = 1;
        }
    }
}

void exec_cmd(char *cmd, t_shell *minishell)
{
    char **args;
    char *path;

    args = ft_split(cmd, ' ');
    if (!args)
    {
        perror("Failed to split command");
        exit(EXIT_FAILURE);
    }

    path = get_path(args[0], minishell);
    if (!path)
    {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        exit(EXIT_FAILURE);
    }

    execve(path, args, minishell->env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}*/