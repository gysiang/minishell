#include "minishell.h"

static void update_env_pwd(t_shell *minishell)
{
    char *old_pwd = get_env_value(minishell, "PWD");
    char *new_pwd = getcwd(NULL, 0);

    if (new_pwd) {
        set_env(minishell, "OLDPWD", old_pwd);
        set_env(minishell, "PWD", new_pwd);
        free(new_pwd);
    }
    if (old_pwd)
        free(old_pwd);
}

int cd_error_messages(int err, char *target_dir, int err_no)
{
    if (err == 1)
        ft_putstr_fd("minishell: cd: too many arguments LOL\n", 2);
    else if (err == 2)
        ft_putstr_fd("minishell: cd: too few arguments HEHEHE\n", 2);
    else
    {
        ft_putstr_fd("minishell: cd: ", 2);
        if (target_dir) {
            ft_putstr_fd(target_dir, 2);
            ft_putstr_fd(": ", 2);
        }
        ft_putstr_fd(strerror(err_no), 2);
        ft_putstr_fd("\n", 2);
    }
    return 1;
}

int minishell_cd(t_shell *minishell)
{
    t_token *cmd_token;

    cmd_token = minishell->cmd_list;
    if (!cmd_token || ft_strcmp(cmd_token->token, "cd") != 0)
        return cd_error_messages(2, NULL, 0);
    t_token *dir_token = cmd_token->next;
    if (!dir_token)
        return cd_error_messages(2, NULL, 0);
    if (dir_token->next)
        return cd_error_messages(1, NULL, 0);    
    if (chdir(dir_token->token) != 0)
        return cd_error_messages(3, dir_token->token, errno);
    update_env_pwd(minishell);
    return 0;
}