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

int redirect_input(t_shell *minishell, t_token *token)
{
    t_token *tracker;
    int 	type;
    char    *file_name;
    int 	fd;
    if (!token)
        return (0);
    tracker = token;
    while (tracker)
    {
        type = tracker->type;
        file_name = (char *)tracker->next->token;
		printf("filename: %s\n", file_name);
        if (type == T_LESSER_THAN)
            fd = open_input(file_name);
        else
            fd = here_doc(minishell, file_name);
        if (fd < 0)
            break;
		tracker = token->next->next;
		//if (tracker)
        //	close(fd);
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
    if (type == T_GREATER_THAN)
        fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    else if (type == T_RIGHT_SHIFT)
        fd = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
    return (fd);
}

int redirect_output(t_token *token)
{
    t_token *tracker;
    int 	type;
    char    *file_name;
    int 	fd;

    fd = -1;
    if (!token)
        return (0);
    tracker = token;
    while (tracker)
    {
        type = tracker->type;
        file_name = (char *)tracker->next->token;
		printf("%s\n", file_name);
        fd = open_output(file_name, type);
        if (fd < 0)
            break;
		/***
        tracker = tracker->next->next;
        if (tracker)
            close(fd);
		**/
    }
    return (fd);
}
/***
void    redirect(t_token *token, int *redir)
{
    redir[0] = redirect_input(minishell);
    if (redir[0] == -1)
        return ;
    redir[1] = redirect_output(t_token *token);
} **/
