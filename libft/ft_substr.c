/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 12:00:36 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 12:48:58 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		ptr = (char *) malloc (sizeof (char));
		if (!ptr)
			return (NULL);
		*ptr = '\0';
		return (ptr);
	}
	if (ft_strlen(s) - start > len)
		i = len + 1;
	else
		i = ft_strlen(s) - start + 2;
	ptr = (char *) malloc ((i) * sizeof (char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, i);
	return (ptr);
}
