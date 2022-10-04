/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/10/04 03:58:43 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_bank(int error)
{
	if (error == 1)
		write (2, "No such file or directory\n", 26);
	else if (error == 258)
		write (2, "Syntax error, unexpected token\n", 31);
	else if (error == -1)
		write (2, "exit\n", 5);
	else if (error)
		write (2, "Error\n", 6);
}

int	handle_error(int error, t_general *gen)
{
	(void) gen;
	error_bank(error);	
	if (error)
		return (-1);
	else
		return (0);
}

int	error_extract_var(t_general *gen)
{
	if (ft_strchr(TOKENS, gen->in[gen->to]))
	{
		gen->error_no = -1;
		return (gen->error_no);
	}
	else
		gen->error_no = 0;
	return (gen->error_no);
}
