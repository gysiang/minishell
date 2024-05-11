#include "minishell.h"

static void update_env_pwd(t_shell *minishell) {
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

static int cd_error_messages(int err, char *target_dir, int err_no) {
    if (err == 1) {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
    } else {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(target_dir, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(err_no), 2);  // Use the strerror function to get a string representation of the error number
        ft_putstr_fd("\n", 2);
    }
    return (1);
}


int minishell_cd(t_shell *minishell) {
    char *target_dir;
    t_token *cmd_token = minishell->cmd_list->next; // Skip 'cd' command token

    if (!cmd_token || cmd_token->type != T_IDENTIFIER) { // No argument or improper token
        target_dir = get_env_value(minishell, "HOME");
    } else if (cmd_token->next) { // Too many arguments
        return cd_error_messages(1, NULL, 0);
    } else if (strcmp(cmd_token->token, "-") == 0) {
        target_dir = get_env_value(minishell, "OLDPWD");
    } else {
        target_dir = cmd_token->token;
    }

    if (chdir(target_dir) != 0) {
        return cd_error_messages(0, target_dir, errno);
    }

    update_env_pwd(minishell);
    return 0;
}