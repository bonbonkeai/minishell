/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:44 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:45 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_question_mark(t_expansion *exp)
{
    exp->i++;
    if (!handle_exit_status(exp))
        return (0);
    return (1);
}

int handle_digit_after_dollar(const char *input, t_expansion *exp)
{
    if (ft_isdigit(input[exp->i]))
    {
        exp->i++;
        return (1);
    }
    return (0);
}

int handle_illegal_or_braces(const char *input, t_expansion *exp, t_env *lst_env)
{
    if (input[exp->i] == '{')
        return (handle_braces(exp, lst_env));
    if (!ft_isalpha(input[exp->i]) && input[exp->i] != '_' && input[exp->i] != '\0')
        return (handle_illegal_dollar(input, exp));
    return (-1);
}
