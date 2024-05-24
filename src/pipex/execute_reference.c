/*void execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
    int pipe_fd[2];
    int pid;
    int num_of_command;
    int status;

    printf("Executing command index: %d\n", i);

    num_of_command = num_of_commands(minishell);
    printf("Total number of commands: %d\n", num_of_command);

    if (i != num_of_command - 1)
    {
        if (pipe(pipe_fd) == -1) {
            perror("Failed to create pipe");
            exit(EXIT_FAILURE);
        } else {
            printf("Pipe created: read fd = %d, write fd = %d\n", pipe_fd[0], pipe_fd[1]);
        }
    }

    pid = fork();
    printf("Fork result: %d\n", pid);

    if (pid == 0)
    {
        // Child process
        printf("Child process for command: %s\n", curr->token);
        if (i != 0)
        {
            printf("Redirecting stdin from fd %d\n", minishell->ret_fd[0]);
            dup2(minishell->ret_fd[0], STDIN_FILENO);
            close(minishell->ret_fd[0]);
        }
        if (!last_command)
        {
            printf("Redirecting stdout to fd %d\n", pipe_fd[1]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
        }
        if (handle_redirection(minishell, curr) != 1)
        {
            exec_cmd(curr->token, minishell);
        }
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        printf("Parent process, waiting for PID: %d\n", pid);
        close(pipe_fd[1]); // Close write end in the parent if not needed
        if (!last_command) {
            minishell->ret_fd[0] = pipe_fd[0];
            printf("Saving read end of pipe for next command: fd %d\n", pipe_fd[0]);
        } else {
            close(pipe_fd[0]);
            printf("Closing read end of pipe: fd %d\n", pipe_fd[0]);
        }
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            minishell->last_return = WEXITSTATUS(status);
            printf("Child exited with status: %d\n", minishell->last_return);
        }
        else
        {
            minishell->last_return = 1;
            printf("Child did not exit normally\n");
        }
    }
}

void exec_cmd(char *cmd, t_shell *minishell) {
    char **s_cmd;
    char *path;
    int return_code;

    printf("Executing command: %s\n", cmd);

    if (!cmd || !minishell) {
        printf("Invalid command or shell context\n");
        ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    if (ft_strncmp(cmd, "$?", 2) == 0) {
        printf("Handling special case for last return status\n");
        printf("%d\n", minishell->last_return);
        minishell->last_return = 0;
        return;
    }

    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd) {
        printf("Failed to split command string\n");
        ft_putstr_fd("Failed to split command\n", STDERR_FILENO);
        minishell->last_return = 1;
        return;
    }

    if (execute_builtin_1(minishell) || execute_builtin_2(minishell) || other_cmds(minishell)) {
        printf("Executed a builtin or other command\n");
        ft_free_tab(s_cmd);
        return;
    }

    path = get_path(s_cmd[0], minishell);
    if (!path) {
        printf("Command not found: %s\n", s_cmd[0]);
        return_code = minishell_error_msg(s_cmd[0], 42);
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        return;
    }

    printf("Executing external command via execve: %s\n", path);
    if (execve(path, s_cmd, minishell->env) == -1) {
        printf("execve failed: %s\n", strerror(errno));
        return_code = minishell_error_msg(s_cmd[0], errno);
        minishell->last_return = return_code;
        ft_free_tab(s_cmd);
        exit(return_code);
    }

    ft_free_tab(s_cmd);
}*/
