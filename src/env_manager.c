#include "minishell.h"

char    *get_env(t_shell *minishell, const char *var)
{
    int i;
    size_t  var_len;

    i = 0;
    var_len = ft_strlen(var);
    while (minishell->env[i])
    {
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=')
           return (ft_strdup(&minishell->env[i][var_len+1]));
        i++;   
    }
    return (NULL);
}
int env_len(t_shell *minishell)
{
    int i;
    
    i = 0;
    while (minishell->env[i])
        i++;
    return (i);
}

int search_env_by_var(t_shell *minishell, const char *var)
{
    int i;
    size_t  var_len;

    i = 0;
    var_len = ft_strlen(var);
    while (minishell->env[i])
    {
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=')
            return (i);
        i++;
    }
    return (-1);
}

void  sort_env(t_shell *minishell)
{
    int i;
    int j;
    int environment_len;

    i = 0;
    environment_len = env_len(minishell);
    while (i < environment_len - 1)
    {
        j = 0;
        while (j < environment_len - i - 1)
        {
            if (ft_strccmp(minishell->env[j], minishell->env[j + 1], '=') > 0)
                ft_strswap(&minishell->env[j], &minishell->env[j + 1]);
            j++;
        }
        i++;
    }
}

void    init_env(t_shell *minishell, const char **envp)
{
    int i;
    int j;
    char    *equal_sign;

    i = 0;
    j = 0;
    minishell->env = (char **)ft_calloc(BASE_ENV_SIZE, sizeof(char *));
    minishell->env_size = BASE_ENV_SIZE;
    while (envp[i])
    {
        equal_sign = ft_strchr(envp[i],'=');
        if (equal_sign && !ft_strnstr(envp[i], "_WORKSPACE_", equal_sign - &envp[i][0]))
        {
            if (j == minishell->env_size - 1)
                env_realloc(minishell);
            minishell->env[i] = ft_strdup(envp[i]);
            if (ft_strncmp (envp[i], "HOME=", 5) == 0)
            {
                free(minishell->home);
                minishell->home = ft_strdup(&envp[i][5]);
            }
            else if (ft_strncmp(envp[i], "PWD=", 4) == 0)
            {
                free(minishell->pwd);
                minishell->pwd = ft_strdup(&envp[i][4]);
            }
            j++;
        }
        i++;
    }
}

