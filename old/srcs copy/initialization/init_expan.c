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

int init_expand(t_expansion *exp)
{
    if (!exp)
        return (0);
    ft_bzero(exp, sizeof(t_expansion));
    exp->str = NULL;
    exp->buf = malloc(INIT_SIZE);
    if (!exp->buf)
        return (0);
    exp->buf[0] = '\0';
    exp->size = INIT_SIZE;
    exp->len = 0;
    exp->i = 0;
    exp->k = 0;;
    exp->in_squote = 0;
    exp->in_dquote = 0;
    exp->exit_status = NULL;
    exp->env_val = NULL;
    exp->var_name = NULL;
    exp->illegal_type = 0;
    exp->error_char = NULL;
    exp->status = 0;
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
	free(exp->str);
	free(exp->exit_status);
	free(exp->env_val);
}
