#include "../includes/minishell.h"

static void signal_free(t_shell *minishell)
{
    if (minishell)
        free_and_exit(minishell, 130);
}

static void signal_exit(int signal_number)
{
    (void)signal_number;
    ft_putchar('\n');
    signal_free(NULL);
}

static void error_EOF(char *end_of_file)
{
    ft_putstr_fd("minishell:warning:", 2);
    ft_putstr_fd("here_document delimited by end-of-file (wanted ",2);
    ft_putstr_fd(end_of_file, 2);
    ft_putendl_fd(")",2);
}

// here_doc_read function

// here_doc implementation
