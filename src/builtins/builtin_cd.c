/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <axlee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:46:40 by axlee             #+#    #+#             */
/*   Updated: 2024/06/03 11:43:08 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *get_home_directory(t_shell *minishell, const char *token)
{
    char *home_dir;

    home_dir = NULL;
    if (token == NULL || ft_strcmp(token, "~") == 0)
    {
        home_dir = get_env_value(minishell, "HOME");
        if (home_dir == NULL)
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
    }
    return (home_dir);
}

static char *resolve_directory(t_shell *minishell, t_token *cmd_token)
{
    t_token *dir_token;
    char *dir;

    dir_token = cmd_token->next;
    if (!dir_token)
    {
        dir = get_home_directory(minishell, NULL);
        if (dir == NULL)
            return (NULL);
    }
    else
    {
        dir = get_home_directory(minishell, dir_token->token);
        if (dir == NULL)
            dir = dir_token->token;
        if (dir_token->next)
        {
            minishell_error_msg("cd", 43);
            return (NULL);
        }
    }
    return (dir);
}

static int update_env_vars(t_shell *minishell, const char *old_pwd, const char *new_pwd)
{
    if (old_pwd)
        set_env(minishell, "OLDPWD", old_pwd);
    if (new_pwd)
        set_env(minishell, "PWD", new_pwd);
    else
    {
        perror("getcwd failed");
        return (1);
    }
    return (0);
}

static int change_directory(t_shell *minishell, const char *dir)
{
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    if (chdir(dir) != 0)
    {
        perror("minishell: cd");
        free(old_pwd);
        return (1);
    }
    new_pwd = getcwd(NULL, 0);
    if (update_env_vars(minishell, old_pwd, new_pwd) != 0)
    {
        free(old_pwd);
        free(new_pwd);
        return (1);
    }
    free(old_pwd);
    free(new_pwd);
    return (0);
}

int minishell_cd(t_shell *minishell)
{
    t_token *cmd_token;
    char *dir;

    cmd_token = minishell->cmd_list;
    if (!cmd_token)
    {
        ft_putstr_fd("minishell: cd: too few arguments\n", 2);
        return (1);
    }
    if (ft_strncmp(cmd_token->token, "cd", 2) != 0)
    {
        minishell_error_msg("cd", 42);
        return (1);
    }
    dir = resolve_directory(minishell, cmd_token);
    if (!dir)
        return (1);
    return (change_directory(minishell, dir));
}
