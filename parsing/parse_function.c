/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 20:11:43 by khatlas           #+#    #+#             */
/*   Updated: 2022/09/01 14:05:12 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_function(t_token **head, t_general *gen)
{
    t_token *it;
    char    *buffer;
    char    cwd[PATH_MAX];

    buffer = NULL;
    if (!head || !*head)
        return (-1);
    int     flag = 0;
    it = *head;
    //check the token in the list of commands (still to work in the external)
    // printf("check_format: %d\n",check_format(it));
    /* APARENTLY IS DONE */
    /* check format for execution */
    if (!check_format(it))
    {
		gen->error_no = -1;
		return (gen->error_no);	
	}
    //get the token in the list and look for the specific case
    if (cmd_searchlst(it) == ECHO_CMD) // echo
        ft_echo(it, gen, flag);
    else if (cmd_searchlst(it) == CD_CMD) // cd
        ft_cd(it);
    else if (cmd_searchlst(it) == PWD_CMD) //pwd
        gen->str = ft_strdup(getcwd(cwd, PATH_MAX));
    else if (cmd_searchlst(it) == EXPORT_CMD)
    {
        //need to break this down into individual function
        ft_export(it, gen);
        // char    *buffer;
        // char    *final;
        // t_env   *existing;

        // final = NULL;
        // it = it->next;
        // buffer = it->content;
        // if (!buffer || !it->next || !check_variable(buffer))
        //     return (-1);
        // existing = find_env(gen->envp, buffer);
        // it = it->next;
        // if (!it->content || it->content[0] != '=')
        //     return (-1);
        // final = ft_strjoin(buffer, it->content);
        // if (existing)
        // {
        //     if (ft_export_replace(&gen->envp, final, existing->name))
        //     {
        //         free (final);
        //         gen->error_no = -1;
        //         return (gen->error_no);
        //     }
        // }
        // else
        // {
        //     if (ft_export(&gen->envp, final))
        //     {
        //         free (final);
        //         gen->error_no = -1;
        //         return (gen->error_no);
        //     }
        // }
        // free (final);
    }
    else if (cmd_searchlst(it) == UNSET_CMD)
    {
        t_env   *existing;

        it = it->next;
        if (!it || !it->content)
        {
            gen->error_no = -1;
            return (gen->error_no);
        }
        existing = find_env(gen->envp, it->content);
        if (existing)
        {
            if (ft_unset(&gen->envp, existing->name))
            {
                gen->error_no = -1;
                return (gen->error_no);
            }
        }
    }
    else if (cmd_searchlst(it) == ENV_CMD)
        gen->str = ft_env(gen->envp);
    else if (cmd_searchlst(it) == EXIT_CMD)
    {
        gen->error_no = 1;
        return (gen->error_no);
    }
    {
        //here I will set the $_ to the last sent arg, given that there's not been an error
        t_token *last;
        char    *holder;

        holder = ft_strjoin("_", "=");
        last = token_last(*head);
        holder = ft_strjoinfree(holder, ft_strdup(last->content));
        //have to consider that a token may be last, in which case content would be NULL
        //but from testing I think then I shouldnt overwrite the last input arg
        if (!last->content || ft_export_replace_exe(&gen->envp, holder, "_"))
        {
            gen->error_no = -1;
            return (gen->error_no);
        }
        free (holder);
    }
    // //temporary output
    if (gen->str)
    {
        printf("%s", gen->str);
        if (flag)
            printf("%%\n");
        else
            printf("\n");
    }
    //
    return (0);
}