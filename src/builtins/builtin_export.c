/* 
EXPORT FUNCTION BEING READ BUT THE VALUES ARE NOT BEING UNPDATED IN THE ENV.

POTENTIALLY ISSUES INSIDE THE ENV NOT BEING UPDATED?
*/


#include "minishell.h"

static char *get_var_name(char *cmd) {
    char *equal_pos = ft_strchr(cmd, '=');
    if (equal_pos != NULL) {
        return ft_substr(cmd, 0, equal_pos - cmd);
    }
    return NULL;
}

void env_realloc(t_shell *minishell)
{
    char **new_env;
    int old_size = minishell->env_size;
    minishell->env_size *= 2;
    new_env = (char **)realloc(minishell->env, minishell->env_size * sizeof(char *));
    if (new_env == NULL) {
        ft_putendl_fd("minishell: memory allocation failed", 2);
        free_and_exit(minishell, 1);
    }
    minishell->env = new_env;
    printf("Environment reallocated. New size: %d\n", minishell->env_size);
    int  i = old_size;
    while (i < minishell->env_size){
        minishell->env[i] = NULL;
        i++;
    }
    printf("Environment initialization complete \n");
}

static int is_valid_identifier(const char *str)
{
    if (str == NULL || *str == '\0' || ft_isdigit(*str))
        return (0);
    while (*str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
        str++;
    }
    return (1);
}

static int save_var(t_shell *minishell, char *content) {
    char *var_name;
    int var_index;

    if (!is_valid_identifier(content)) {
        ft_putstr_fd("minishell: export: '", 2);
        ft_putstr_fd(content, 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        return 1;
    }

    var_name = get_var_name(content);
    if (!var_name)
        return 0;

    var_index = search_env_by_var(minishell, var_name);
    free(var_name);

    if (var_index == -1)
        var_index = env_len(minishell);

    if (var_index == minishell->env_size) {
        printf("Environment size reached. Reallocating...\n");
        env_realloc(minishell);
    }

    free(minishell->env[var_index]);
    minishell->env[var_index] = ft_strdup(content);
    printf("Variable '%s' saved at index %d\n", content, var_index);
    printf("New value: '%s'\n", minishell->env[var_index]);

    return 0;
}

void print_vars(t_shell *minishell) {
    int i;
    printf("entered into print_vars\n");

    for (i = 0; i < env_len(minishell); i++) {
        printf("Variable %d: %s\n", i, minishell->env[i]);
    }
}

int minishell_export(t_shell *minishell) {
    t_token *token = minishell->cmd_list->next; // Assuming cmd_list is the head of tokens

    if (!token) {
        print_vars(minishell);
        return 0;
    }

    while (token) {
        if (token->type == T_ENV_ASSIGNMENT) {
            printf("Processing token: %s\n", token->token);
            if (save_var(minishell, token->token)) {
                printf("Failed to save the variable %s\n", token->token);
                return 1; // Set error code if any variable save fails
            }
        }
        token = token->next;
    }

    sort_env(minishell); // Assuming this function sorts the environment variables
    printf("Environment variables sorted\n");
    return 0;
}
