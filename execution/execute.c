/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:15:13 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/20 04:17:10 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_pipes(int pipe_count, int *pipefds)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			printf("piping fails\n");
			exit (-1);
		}
		i++;
	}
}

int	execute_prep(t_general *gen)
{
	t_execute	exevars;
	t_matrix	*matrix;

	matrix = gen->matrix;
	ft_bzero(&exevars, sizeof(t_execute));
	exevars.pipe_count = count_operators(gen->matrix, OPERATOR);
	exevars.pipefds = malloc (sizeof (int) * (exevars.pipe_count * 2));
	open_pipes(exevars.pipe_count, exevars.pipefds);
	exevars.index = 0;
	exevars.flag = 1;
	exe_cmd (gen->matrix, &exevars, &gen->envp);
	free (exevars.pipefds);
	return (0);
}
