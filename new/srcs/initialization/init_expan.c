/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:10 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:43:12 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int init_expand(t_expansion *exp, char *input, int status)
// {
//     if (!exp)
//         return (0);
//     ft_bzero(exp, sizeof(t_expansion));
//     free(exp->str);
//     exp->str = ft_strdup(input);
//     if (!exp->str)
//         return (0);
//     exp->buf = malloc(INIT_SIZE);
//     if (!exp->buf)
//         return (free(exp->str), 0);
//     exp->buf[0] = '\0';
//     exp->size = INIT_SIZE;
//     exp->len = 0;
//     exp->i = 0;
//     exp->k = 0;
//     exp->in_squote = 0;
//     exp->in_dquote = 0;
//     exp->env_val = NULL;
//     exp->var_name = NULL;
//     exp->status = status;
//     free(exp->exit_status);
//     exp->exit_status = ft_itoa(status);
//     if (!exp->exit_status)
//         return (free(exp->str), free(exp->buf), 0);
//     exp->illegal_type = SUFFIX_OK;
//     exp->error_char = NULL;
//     return (1);
// }

static int reset_and_alloc_expand(t_expansion *exp, char *input)
{
    ft_bzero(exp, sizeof(t_expansion));
    free(exp->str);
    exp->str = ft_strdup(input);
    if (!exp->str)
        return (0);
    exp->buf = malloc(INIT_SIZE);
    if (!exp->buf)
        return (free(exp->str), 0);
    exp->buf[0] = '\0';
    exp->size = INIT_SIZE;
    exp->len = 0;
    return (1);
}

static int init_expand_flags(t_expansion *exp, int status)
{
    exp->i = 0;
    exp->k = 0;
    exp->in_squote = 0;
    exp->in_dquote = 0;
    exp->env_val = NULL;
    exp->var_name = NULL;
    exp->status = status;
    free(exp->exit_status);
    exp->exit_status = ft_itoa(status);
    if (!exp->exit_status)
        return (0);
    exp->illegal_type = SUFFIX_OK;
    exp->error_char = NULL;
    return (1);
}

int init_expand(t_expansion *exp, char *input, int status)
{
    if (!exp)
        return (0);
    if (!reset_and_alloc_expand(exp, input))
        return (0);
    if (!init_expand_flags(exp, status))
    {
        free(exp->str);
        free(exp->buf);
        return (0);
    }
    return (1);
}


int get_tab_num(char **tab)
{
    int i;
    
    i = 0;
    if (!tab)
        return (0);
    while (tab[i])
        i++;
    return (i);
}


void	free_expansion(t_expansion *exp)
{
	if (!exp)
		return ;
    free(exp->buf);
    exp->buf = NULL;
    free(exp->str);
	exp->str = NULL;
    exp->env_val = NULL;
    free(exp->var_name);
    exp->var_name = NULL;
    free(exp->exit_status);
    exp->exit_status = NULL;
    free(exp->error_char);
    exp->error_char = NULL;
}
