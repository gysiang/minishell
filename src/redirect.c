#include "../includes/minishell.h"

static int open_input(char *file_name)
{
    struct stat buffer;
    int fd;

    if (stat(file_name, &buffer) == -1 || S_ISDIR(buffer.st_mode))
    {
        minishell_error_msg(file_name, 2);
        return (-1);
    }
        if (access(file_name,R_OK) == -1)
    {
        minishell_error_msg(file_name, 3);
        return (-1);
    }
    fd = open(file_name,O_RDONLY);
    printf("Trying to open file: %s\n", file_name);
    printf("Open returned: %d\n", fd);  
    if (fd == -1)
    {
        perror("open");
        return (fd);
    }
    return (fd);
    
}

static int redirect_input(t_shell *minishell, t_list *input)
{
    t_list *tracker;
    int type;
    char    *file_name;
    int fd;
    if (!input)
        return (0);
    tracker = input;
    while (tracker)
    {
        type = ((char *)tracker->content)[0] - 48;
        file_name = &((char *)tracker->content)[1];
        if (type == 1)
            fd = open_input(file_name);
        else
            fd = here_doc(minishell, file_name);
        if (fd < 0)
            break;
        tracker = tracker->next;
        if (!tracker)
            close(fd);
    }
    return (fd);
}

static int open_output(char *file_name, int type)
{
    struct stat buffer;
    int fd;

    fd = 0;
    if (stat(file_name, &buffer) == 0 && S_ISDIR(buffer.st_mode))
    {
        minishell_error_msg(file_name, 2);
        return (-1);
    }
    if (access(file_name, W_OK) == -1)
    {
        minishell_error_msg(file_name, 3);
        return (-1);
    }
    if (type == 1)
        fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else if (type == 2)
        fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
    return (fd);
}

static int redirect_output(t_list *output)
{
    t_list *tracker;
    int type;
    char    *file_name;
    int fd;

    fd = -1;
    if (!output)
        return (0);
    tracker = output;
    while (tracker)
    {
        type = ((char *)tracker->content)[0] - 48;
        file_name = &((char *)tracker->content)[1];
        fd = open_output(file_name, type);
        if (fd < 0)
            break;
        tracker = tracker->next;
        if (tracker)
            close(fd);
    }
    return (fd);
}

void    redirect(t_shell *minishell, t_cmd *cmd, int *redir)
{
    redir[0] = redirect_input(minishell, cmd->input);
    if (redir[0] == -1)
        return ;
    redir[1] = redirect_output(cmd->output);
}