#include "../includes/minishell.h"

void    free_and_exit(t_shell *minishell, int return_value)
{
    rl_clear_history();
    ft_split_free(&minishell->env);
    ft_lstclear(&minishell->cmd_list,delete_command);
    free(minishell->home);
    free(minishell->pwd);
    free(minishell->prompt);
    exit(return_value);
}

void    delete_command(void *elem)
{
    t_cmd   *cmd;

    cmd = (t_cmd*)elem;
    ft_split_free(&cmd->argv);
    ft_lstclear(&cmd->input, free);
    ft_lstclear(&cmd->output, free);
    free(cmd);
}

char *ft_strjoin_free(char **s1, char const *s2)
{
    char *result;

    if (!s1 || !s2)
        return (NULL);
    if (!*s1)
    {
        *s1 = ft_strdup("");
        if (!*s1)
            return (NULL);
    }
    result = ft_strjoin(*s1, s2);
    free(*s1);
    *s1 = NULL;
    return (result);
}

int minishell_error_msg(char *cmd, int error_no)
{
    static char  *error_messages[4] = {
        "command not found",
        "No such file or directory",
        "Is a directory",
        "Permission denied"
    };
    char    *error;
    int return_no;

    error = ft_strdup("minishell: ");
    error = ft_strjoin_free(&error, cmd);
    error = ft_strjoin(&error, ":");
    if (error_no >= 0 && error_no <= 3)
        error = ft_strjoin_free(&error, error_messages[error_no]);
    else
        error = ft_strjoin_free(&error, strerror(error_no));
    ft_putendl(error_no);
    free(error);
    if (error_no == 0 || error_no == -1)
        return_no = 127;
    else
        return_no = 126;
    return (return_no);
}
