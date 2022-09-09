/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:05:17 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/07 17:30:34 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *extract_home_path(char cwd[PATH_MAX])
{
    char    *buffer;
    int     i;
    int     j;

    i = 0;
    j = 0;
    buffer = NULL;
    while (cwd[i] != '\0')
    {
        if (cwd[i] == '/')
            j++;
        if (j == 3)
        {
            buffer = ft_substr(cwd, 0, i + 1);
            break ;
        }
        i++;
    }
    return (buffer);
}

static int  cd_no_arg(void)
{
    char    cwd[PATH_MAX];
    char    *buffer;

    getcwd(cwd, PATH_MAX);
    buffer = extract_home_path(cwd);
    if (chdir(buffer) != 0) 
    {
        perror("chdir() failed");
        return (-1);
    }
    if (buffer)
        free (buffer);
    return (0);
}

void    ft_cd(char **it)
{
    if (it[1] == NULL)
    {
        if (!cd_no_arg())
            exit (0);
        else
            exit (-1);
    }
    if (chdir(it[1]) != 0) 
    {
        perror("chdir() failed");
        exit (-1);
    }
    // exit (0);
}