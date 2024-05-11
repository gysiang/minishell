#include "minishell.h"

char *get_env_value(t_shell *minishell, const char *var) {
    int i = 0;
    size_t var_len = ft_strlen(var);
    printf("Debug: Searching for variable '%s'\n", var);
    while (minishell->env[i]) {
        printf("Debug: Checking env[%d]: %s\n", i, minishell->env[i]);
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=') {
            printf("Debug: Found variable '%s' at index %d\n", var, i);
            return ft_strdup(&minishell->env[i][var_len + 1]);
        }
        i++;
    }
    printf("Debug: Variable '%s' not found\n", var);
    return (NULL);
}


int env_len(t_shell *minishell) {
    int i = 0;
    while (minishell->env[i]) {
        i++;
    }
    printf("Debug: Total environment variables count: %d\n", i);
    return (i);
}


int search_env_by_var(t_shell *minishell, const char *var) {
    int i = 0;
    size_t var_len = ft_strlen(var);
    while (minishell->env[i]) {
        if (ft_strncmp(minishell->env[i], var, var_len) == 0 && minishell->env[i][var_len] == '=') {
            printf("Debug: Found environment variable '%s' at index %d\n", var, i);
            return i;
        }
        i++;
    }
    printf("Debug: Environment variable '%s' not found\n", var);
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

// Issue here where is ts being fed unitialized data

// Memory issues when doing minishell cd
void set_env(t_shell *minishell, const char *var, const char *value) {
    printf("Debug: Setting environment variable '%s' to '%s'\n", var, value);
    int idx = search_env_by_var(minishell, var);
    size_t var_len = ft_strlen(var);
    size_t value_len = ft_strlen(value);
    char *new_entry = malloc(var_len + value_len + 2);
    if (!new_entry) {
        perror("Failed to allocate memory for new environment variable");
        return;
    }
    ft_strcpy(new_entry, var);
    new_entry[var_len] = '=';
    ft_strcpy(&new_entry[var_len + 1], value);
    if (idx != -1) {
        free(minishell->env[idx]);
        minishell->env[idx] = new_entry;
        printf("Debug: Replaced old environment variable at index %d\n", idx);
    } else {
        int current_length = env_len(minishell);
        if (minishell->env_size <= current_length + 1) {
            env_realloc(minishell);
        }
        minishell->env[current_length] = new_entry;
        minishell->env[current_length + 1] = NULL;
        printf("Debug: Added new environment variable at index %d\n", current_length);
    }
}


void init_env(t_shell *minishell, const char **envp) {
    printf("Debug: Initializing environment from envp\n");
    int i = 0, j = 0;
    minishell->env = (char **)ft_calloc(BASE_ENV_SIZE, sizeof(char *));
    minishell->env_size = BASE_ENV_SIZE;
    while (envp[i]) {
        printf("Debug: Processing envp[%d]: %s\n", i, envp[i]);
        char *equal_sign = ft_strchr(envp[i], '=');
        if (equal_sign && !ft_strnstr(envp[i], "_WORKSPACE_", equal_sign - &envp[i][0])) {
            if (j == minishell->env_size - 1) {
                env_realloc(minishell);
            }
            minishell->env[j] = ft_strdup(envp[i]);
            j++;
        }
        i++;
    }
    printf("Debug: Environment initialized with %d variables\n", j);
}
