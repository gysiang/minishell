#include "minishell.h"

static char *alloc_cwd(void)
{
    char    *buffer;
    size_t  size;

    size = 1024;
    buffer = getcwd(NULL,size);
    if (buffer == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    return (buffer);
}

static void update_env_pwd(t_shell *minishell)
{
    char    *old_pwd_var;
    char    *current_pwd;
    char    *argv[4];
    size_t  pwd_len;
    size_t  oldpwd_len;

    current_pwd = alloc_cwd();
    old_pwd_var = get_env(minishell, "PWD");
    argv[0] = "export";
    pwd_len = ft_strlen(current_pwd);
    argv[1] = malloc(pwd_len + 5);
    ft_strcpy(argv[1], "PWD=");
    ft_strcat(argv[1], current_pwd);
    oldpwd_len = ft_strlen(old_pwd_var);
    argv[2] = malloc(oldpwd_len + 8);
    ft_strcpy(argv[2], "OLDPWD=");
    ft_strcat(argv[2], old_pwd_var);
    argv[3] = NULL;
    minishell_export(minishell, argv);
    free(minishell->pwd);
    minishell->pwd = current_pwd;
    free(old_pwd_var);
    free(argv[1]);
    free(argv[2]);
}

static int  cd_error_messages(int err, char *target_dir, int err_no)
{
    char    *error_msg;
    size_t  msg_len;

    if (err == 1)
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
    else
    {
        msg_len = ft_strlen("minishell: cd: ") + ft_strlen(target_dir) + ft_strlen(" ") + ft_strlen(strerror(err_no)) + 2;
        error_msg = malloc(msg_len + 1);
        if (!error_msg)
            return (1);
        ft_strcpy(error_msg, "minishell: cd: ");
        ft_strcat(error_msg, target_dir);
        ft_strcat(error_msg, ": ");
        ft_strcat(error_msg, strerror(err_no));
        ft_strcat(error_msg, "\n");
        ft_putstr_fd(error_msg, 2);
        free(error_msg);
    }
    return (1);
}

int minishell_cd(t_shell *minishell, t_cmd *cmd)
{
    char    *target_dir;

    if (cmd->argc > 2)
    {
        cmd->return_value = cd_error_messages(1, NULL, 0);
        return (cmd->return_value);
    }
    if (!cmd->argv[1])
        target_dir = get_env(minishell, "HOME");
    else if (ft_strcmp(cmd->argv[1],"-") == 0)
        target_dir = get_env(minishell, "OLDPWD");
    else
        target_dir = cmd->argv[1];
    if (chdir(target_dir))
        cmd->return_value = cd_error_messages(0, target_dir, errno);
    else
    {
        update_env_pwd(minishell);
        if (target_dir != cmd->argv[1])
            free(target_dir);
    }
    return (cmd->return_value);
}
