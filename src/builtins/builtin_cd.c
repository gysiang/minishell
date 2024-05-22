/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:46:40 by axlee             #+#    #+#             */
/*   Updated: 2024/05/18 07:46:46 by axlee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// OLDPWD IS NOT BEING UPDATED IN THE ENV (STILL STUCKED AT MINISHELL/SRC)
// HOWEVER CODE IS FUNCTIONING PROPERLY

// cd src src is not displaying as cd: too many arguments
// cd builtins/builtins: No such file or directory is not being displayed

#include "minishell.h"

static int change_and_check_error(t_shell *minishell, char *dir)
{
    if (chdir(dir) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(dir, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        return (1);
    }
    else
    {
        char *old_pwd = get_env_value(minishell, "PWD");
        char *new_pwd = getcwd(NULL, 0);
        if (old_pwd)
        {
            set_env(minishell, "OLDPWD", old_pwd);
            free(old_pwd);
        }
        set_env(minishell, "PWD", new_pwd);
        free(new_pwd);
    }
    return (0);
}

int minishell_cd(t_shell *minishell)
{
    t_token *cmd_token;
    t_token *dir_token;
    char *dir;

    cmd_token = minishell->cmd_list;
    if (!cmd_token)
    {
        ft_putstr_fd("minishell: cd: too few arguments 1\n", 2);
        return (1);
    }
    if (ft_strncmp(cmd_token->token, "cd", 2) != 0)
    {
        ft_putstr_fd("minishell: cd: command not found 2\n", 2);
        return (1);
    }
    dir_token = cmd_token->next;
    if (!dir_token)
    {
        dir = get_env_value(minishell, "HOME");
        if (dir == NULL)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else
    {
        dir = dir_token->token;
        if (dir_token->next)
        {
            ft_putstr_fd("minishell: cd: too many arguments\n", 2);
            return (1);
        }
    }
    if (change_and_check_error(minishell, dir) != 0)
    {
        return (1);
    }
    return (0);
}
