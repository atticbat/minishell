/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khatlas < khatlas@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:05:09 by khatlas           #+#    #+#             */
/*   Updated: 2022/08/17 15:02:05 by khatlas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  extract_token(char *in, t_token **head)
{
    int i;

    i = 0;
    if (in[i + 1] == in[i])
    {
        if (in[i] == '<')
            token_add_back(head, token_new('-', NULL));
        if (in[i] == '>')
            token_add_back(head, token_new('+', NULL));
        i++;
    }
    else
        token_add_back(head, token_new(in[i], NULL));
    return (i + 1);
}

static int  extract_quote(char *in, t_token **head)
{
    int i;

    i = 1;
    while (in[i] != '\0')
    {
        if (in[i] == in[0])
        {
            if (in[0] == '\'')
                token_add_back(head, token_new('s', ft_substr(in, 1, i - 1)));
            else if (in[0] == '\"')
                token_add_back(head, token_new('d', ft_substr(in, 1, i - 1)));
            i++;
            break ;
        }
        i++;
    }
    return(i);
}

static int  extract_variable(char *in, t_token **head)
{
    int i;

    i = 1;
    if (ft_strchr(WHITESPACE, in[i]))
    {
        token_add_back(head, token_new('a', ft_substr(in, 0, 1)));
        return (i);
    }
    while (in[i] != '\0')
    {
        if (ft_strchr(WHITESPACE, in[i + 1]) || ft_strchr(TOKENS, in[i + 1]) \
            || in[i + 1] == '\0')
        {
            token_add_back(head, token_new('$', ft_substr(in, 1, i)));
            i++;
            break ;
        }
        i++;
    }
    return(i);
}

static void get_token(char *in, t_general *gen, t_token **head)
{
    int i;
    int j;
    int flag;

    (void) gen;
    i = 0;
    j = 0;
    flag = 0;
    if (ft_strchr(WHITESPACE, in[0]))
        flag = 1;
    while (in[i] != '\0')
    {
        if (in[i] == '$')
        {
            i += extract_variable(in + i, head);
            j = i;
            flag = 1;
            continue ;
        }
        if (ft_strchr(QUOTES, in[i]))
        {
            i += extract_quote(in + i, head);
            j = i;
            flag = 1;
            continue ;
        }
        if ((ft_strchr(WHITESPACE, in[i]) || ft_strchr(TOKENS, in[i])) && !flag && i != j)
        {
            token_add_back(head, token_new('a', ft_substr(in, j, i - j)));
            flag = 1;
            j = i;
            continue ;
        }
        if (ft_strchr(TOKENS, in[i]))
        {
            i += extract_token(in + i, head);
            if (!ft_strchr(WHITESPACE, in[i]))
                flag = 0;
            j = i;
            continue ;
        }
        if ((ft_strchr(WHITESPACE, in[i])) && flag)
        {
            i++;
            j = i;
            if (!ft_strchr(WHITESPACE, in[i]) && !ft_strchr(TOKENS, in[i]))
                flag = 0;
            continue ;
        }
        i++;
    }
    if (i != j)
    {
        while (ft_strchr(WHITESPACE, in[j]))
            j++;
        token_add_back(head, token_new('a', ft_substr(in, j, i - j)));
    }
}

void	reset(t_general *gen, t_token **head)
{
    (void) gen;
    token_clear(head, free);
}

void	parse_token(t_general *gen, t_token **head, char *inpt)
{
    int i;

    i = 0;
	while (ft_strchr(WHITESPACE, inpt[i]))
		i++;
	inpt += i;
    get_token(inpt, gen, head);
    print_all(*head);
	reset(gen, head);
}