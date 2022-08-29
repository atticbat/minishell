/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:34:58 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/29 07:43:29 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *find_env(t_env *envp, char *search)
{
   	t_env	*buffer;
    size_t  len;

    if (!envp || !search)
        return (NULL);
    len = ft_strlen(search);
	buffer = envp;
	while (buffer != NULL)
	{
        if (!ft_strncmp(buffer->name, search, (int) len) \
            && ft_strlen(buffer->name) == len)
            return (buffer);
		buffer = buffer->next;
	}
    return (NULL);
}

char    *ft_getenv(t_env *envp, char *search)
{
	t_env	*buffer;

    buffer = find_env(envp, search);
    if (!buffer || !buffer->content)
        return (NULL);
    else
        return (ft_strdup(buffer->content));
}