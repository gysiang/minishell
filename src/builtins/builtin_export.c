#include "minishell.h"

static char *get_var_name(char *cmd)
{
    char    *equal_pos;

    equal_pos = ft_strchr(cmd , '=');
    if (equal_pos != NULL)
        return (ft_substr(cmd, 0, equal_pos - cmd));
    return (NULL);
}

static char *export_home_expand(t_shell *minishell, char *content)
{
    char *expanded_content;
    char *home_value;
    int expanded_size;
    int i;
    int j;
    int k;

    expanded_content = NULL;
    home_value = get_env_value(minishell, "HOME");
    if (home_value != NULL)
    {
        expanded_size = strlen(content) + strlen(home_value) + 1;
        expanded_content = (char *)malloc(expanded_size * sizeof(char));
        i = 0;
        j = 0;
        while (content[i] != '\0')
        {
            if (content[i] == '~')
            {
                k = 0;
                while (home_value[k] != '\0')
                {
                    expanded_content[j] = home_value[k];
                    j++;
                    k++;
                }
            }
            else
            {
                expanded_content[j] = content[i];
                j++;
            }
            i++;
        }
        expanded_content[j] = '\0';
    }
    free(home_value);
    return expanded_content;
}

static int  save_var(t_shell *minishell, char *content)
{
    char    *var_name;
    int     var_index;

    if (!ft_isalpha(content[0]))
    {
        ft_putstr_fd("minishell: export: '", 2);
        ft_putstr_fd(content, 2);
        ft_putstr_fd("': not a valid parameter\n", 2);
        return (1);
    }
    var_name = get_var_name(content);
    if (var_name == NULL)
        return (0);
    var_index = search_env(minishell, var_name);
    free(var_name);
    if (var_index == -1)
        var_index = env_len(minishell);
    if (var_index == minishell->env_size - 1)
        env_realloc(minishell);
    free(minishell->env[var_index]);
    minishell->env[var_index] = export_home_expand(minishell, content);
    return (0);
}

static void print_vars(t_shell *minishell)
{
    int i;

    i = 0;
    while (minishell->env[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(minishell->env[i], 1);
        i++;
    }
}

void    env_realloc(t_shell *minishell)
{
    char    **new_env;

    minishell->env_size *= 2;
    new_env = (char **)realloc(minishell->env, minishell->env_size * sizeof(char *));
    if (new_env == NULL)
    {
        ft_putendl_fd("minishell: memory allocation failed", 2);
        free_and_exit(minishell, 1);
    }
    minishell->env = new_env;
}

int minishell_export(t_shell *minishell, t_cmd *cmd)
{
    int i;

    i = 1;
    if (cmd->argc == 1)
        print_vars(minishell);
    while (cmd->argv[i])
    {
        if (save_var(minishell, cmd->argv[i]))
        {
            cmd->return_value = 1;
            return (1);
        }
        i++;
    }
    sort_env(minishell);
    cmd->return_value = 0;
    return (0);
}