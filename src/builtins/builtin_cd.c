/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyong-si <gyong-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:53:07 by axlee             #+#    #+#             */
/*   Updated: 2024/05/04 15:36:05 by gyong-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OLDPWD IS NOT BEING UPDATED IN THE ENV
// HOWEVER CODE IS FUNCTIONING PROPERLY

#include "minishell.h"

static void update_env_pwd(t_shell *minishell)
{
    char *old_pwd;
    char *new_pwd;

    old_pwd = get_env_value(minishell, "PWD");
    new_pwd = getcwd(NULL, 0);
    printf("Updating PWD and OLDPWD\n");
    printf("Old PWD: %s\n", old_pwd ? old_pwd : "(null)");
    printf("New PWD: %s\n", new_pwd ? new_pwd : "(null)");
    if (new_pwd)
    {
        set_env(minishell, "OLDPWD", old_pwd);
        set_env(minishell, "PWD", new_pwd);
        free(new_pwd);
    }
    if (old_pwd)
        free(old_pwd);
}

int minishell_cd(t_shell *minishell)
{
    t_token *cmd_token;
    t_token *dir_token;

    // Get the command token
    cmd_token = minishell->cmd_list;
    if (!cmd_token)
    {
        ft_putstr_fd("minishell: cd: too few arguments 1\n", 2);
        return 1;
    }
    // Ensure the command is 'cd'
    if (ft_strncmp(cmd_token->token, "cd", 2) != 0)
    {
        ft_putstr_fd("minishell: cd: command not found 2\n", 2);
        return 1;
    }
    // Get the directory token
    dir_token = cmd_token->next;
    if (!dir_token) { // If no directory is provided
        return 1;
    }
    // If there are more than one argument after 'cd'
    if (dir_token->next) {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return 1;
    }
    // Change directory and check for errors
    if (chdir(dir_token->token) != 0) {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(dir_token->token, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        return 1;
    }
    // If chdir is successful, update PWD and OLDPWD
    update_env_pwd(minishell);
    return 0; // Indicate success
}