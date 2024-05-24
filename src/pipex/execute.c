/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:01:14 by gyong-si          #+#    #+#             */
/*   Updated: 2024/05/21 13:49:21 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(int i, t_token *curr, t_shell *minishell, int last_command)
{
    int pipe_fd[2];
    int pid;
    int status;

    if (!last_command)
    {
        if (pipe(pipe_fd) == -1) {
            perror("Failed to create pipe");
            exit(EXIT_FAILURE);
        }
    }
    pid = fork();
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
        if (handle_redirection(minishell, curr) != 1)
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
            minishell->last_return = WEXITSTATUS(status);
        else
            minishell->last_return = 1;
    }
}

void exec_cmd(char *cmd, t_shell *minishell)
{
    char **args;
    char *path;
    int return_code;

    if (!cmd || !minishell)
    {
        ft_putstr_fd("Not enough arguments to exec_cmd\n", STDERR_FILENO);
        minishell->last_return = 1;
        return ;
    }
    if (ft_strncmp(cmd, "$?", 2) == 0)
    {
        printf("%d\n", minishell->last_return);
        minishell->last_return = 0;
        return ;
    }
    args = ft_split(cmd, ' ');
    if (!args)
    {
        perror("Failed to split command");
        minishell->last_return = 1;
        exit(EXIT_FAILURE);
    }
    if (execute_builtin_1(minishell) || execute_builtin_2(minishell) || other_cmds(minishell)) {
        printf("Executed a builtin or other command\n");
        ft_free_tab(args);
        return;
    }
    path = get_path(args[0], minishell);
    if (!path)
    {
        printf("Command not found: %s\n", args[0]);
        return_code = minishell_error_msg(args[0], 42);
        minishell->last_return = return_code;
        ft_free_tab(args);
        return;
    }
    /*printf("Executing external command via execve: %s\n", path);
    if (execve(path, args, minishell->env) == -1) {
        printf("execve failed: %s\n", strerror(errno));
        return_code = minishell_error_msg(args[0], errno);
        minishell->last_return = return_code;
        ft_free_tab(args);
        exit(return_code);
    }*/ //Output from this is giving different results as compared to bash: 12,17,141 as compared to 11,11,90 when executing ls | wc
    execve(path, args, minishell->env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}