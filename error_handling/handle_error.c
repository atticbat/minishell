/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 10:26:08 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/31 10:48:12 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(int error, char *inpt, t_token **head, t_general *gen)
{
	//put printing here based on err_no
	if (error == 1)
	{
		write (2, "you typed exit xddd lmao\n", 25); //temp
		free_all(inpt, head, gen);
		// system("leaks minishell");
		exit (0);
	}
	else if (error)
		write (2, "regular error xdd haha\n", 23); //temp
	else
		return (0);
	return (-1);
}