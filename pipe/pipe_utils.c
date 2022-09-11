/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 14:50:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/11 13:22:42 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(t_matrix *matrix)
{
	int i;
	i = 0;
	while (matrix != NULL)
	{
		if (ft_strchr(OPERATOR, matrix->operator))
			i++;
		matrix = matrix->next;
	}
	return (i);
}

static void execute(char *cmd_path, char **arg)
{
	if (cmd_path)
		if (execv(cmd_path, arg) == -1)
			exit (-1);
	exit (0);
}

static int  redirect_right(t_matrix *matrix)
{
	if (matrix && matrix->operator == '>')
	{
		int fd;
		fd = open (matrix->next->matrix[0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			return (-1);
		dup2(fd, STDOUT_FILENO);
		close (fd);
	}
	else if (matrix && matrix->operator == '+')
	{
		int fd;
		fd = open (matrix->next->matrix[0], O_CREAT | O_WRONLY | O_APPEND, 0777);
        if (fd == -1)
            return (-1);
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    else
        return (-1);
    return (0);
}

int find_pipes(t_matrix *matrix)
{
    int i;

    i = 0;
    while (matrix)
    {
        if (matrix->operator == '|')
            i++;
        matrix = matrix->next;
    }
    return (i);
}

static void exe_pipe(t_matrix *matrix, int pipe_count, int *pipefds, int j)
{
    pid_t   pid;
    char    *buffer;
    int     i;

    buffer = NULL;
    pid = fork();
    if (pid == 0) //child
    {
        if (matrix->next && matrix->next->operator != '-')
        {
            if (dup2(pipefds[j + 1], 1) == -1)
                printf("redirect stdout didnt work!\n");
        }
        if (j != 0)
        {
            if (dup2(pipefds[j - 2], 0) == -1)
                printf("redirect stdin didnt work!\n");
        }
        i = 0;
        if (matrix->next && matrix->next->operator == '-')
        {
            if (matrix->next->next->matrix[0])
            {
                char    *buffer2;
                int     filetemp;

                filetemp = open (PATH_FILE_1, O_WRONLY | O_CREAT | O_TRUNC, 0777);
                buffer2 = NULL;
                while (1)
                {
                    write(1, HEREDOC, 9);
                    buffer2 = get_next_line(0);
                    if (!ft_strncmp(matrix->next->next->matrix[0], buffer2, ft_strlen(matrix->next->next->matrix[0])))
                        break ;
                    ft_putstr_fd(buffer2, filetemp);
                    free (buffer2);
                }
                close (filetemp);
                filetemp = open (PATH_FILE_1, O_RDONLY, 0777);
                dup2(filetemp, STDIN_FILENO);
                close (filetemp);
            }
        }
        if (matrix->next && matrix->next->operator == '<')
        {
            int fd;
            fd = open (matrix->next->next->matrix[0], O_CREAT | O_RDONLY, 0777);
            if (fd == -1)
            {
                printf("error file not found");
                exit (-1);
            }
            if (matrix->next && matrix->next->next && matrix->next->next->next)
                redirect_right(matrix->next->next->next);
            dup2(fd, STDIN_FILENO);
            close (fd);
        }
        redirect_right(matrix->next);
        while (i < 2 * pipe_count) //close all fds in current child since we've already made our redirections
        {
            close(pipefds[i]);
            i++;
        }
        buffer = find_path_str(matrix->matrix[0]);
        if (!buffer)
            printf("find path didnt work! (end of child)\n");
        execute(buffer, matrix->matrix);
    }
}

void    exe_cmd(t_matrix *matrix, int pipe_count)
{
    int status;
    int i;
    int j;
    int *pipefds;

    pipefds = malloc (sizeof (int) * (pipe_count * 2));
    i = 0;
    while (i < pipe_count)
    {
        if (pipe(pipefds + i * 2) < 0) //open up all the fds here
        {
            printf("piping fails\n");
            exit (-1);
        }
        i++;
    }
    j = 0;
    while (matrix)
    {
        if (matrix->operator == '|')
        {
            matrix = matrix->next;
            continue ;
        }
        if (matrix->operator == '>' || matrix->operator == '+' || matrix->operator == '<' || matrix->operator == '-')
        {
            matrix = matrix->next;
            if (matrix)
                matrix = matrix->next;
            continue ;
        }
        // printf("matrix[0]: '%s'\n", matrix->matrix[0]);
        exe_pipe (matrix, pipe_count, pipefds, j);
        if (matrix)
            matrix = matrix->next;
        j += 2;
    }
    i = 0;
    while (i < pipe_count * 2)
    {
        close (pipefds[i]);
        i++;
    }
    i = 0;
    while (i < pipe_count + 1)
    {
        wait (&status);
        i++;
    }
}