/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:52:29 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/06 18:55:17 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_args(t_token *it)
{
    int i;

    i = 0;
    while (it && it->type == 'a')
    {
        it = it->next;
        i++;
    }
    return (i);
}

char    **extract_matrix(t_token **it)
{
    char    **matrix_c; 
    int     len;
    int     i;

    len = count_args(*it);
    i = 0;
    matrix_c = malloc (sizeof(char *) * (len + 1));
    matrix_c[len] = NULL;
    while (*it && (*it)->type == 'a')
    {
        if ((*it)->content[ft_strlen((*it)->content) - 1] == ' ' \
            && (ft_strncmp(matrix_c[0], "echo", 4) \
            && ft_strlen(matrix_c[0]) == 4))
            (*it)->content[ft_strlen((*it)->content) - 1] = '\0'; 
        matrix_c[i] = ft_strdup((*it)->content);
        *it = (*it)->next;
        i++;
    }
    return (matrix_c);
}