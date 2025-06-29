
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:46:02 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:46:04 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_home(char *str, t_shell *sh)
{
	char *home;
	char *rest;
	char *result;

    home = get_env_value(sh->env, "HOME");
    if (!home)
        return (ft_strdup(str));
    if (str[1] == '\0')
		return (ft_strdup(home));
    rest = ft_strdup(str + 1);
    if (!rest)
        return (NULL);
    result = ft_strjoin(home, rest);
    free(rest);
    return (result);
}

// char *expand_string(char *str, t_shell *sh, t_suffix_type *out_type, char *error_char)
// {
//     t_expansion exp;
//     char *result;
//     t_env *env;
//     char *home;

//     if (!str)
//         return (NULL);
//     if (str[0] == '~' && (!str[1] || str[1] == '/'))
//     {
//         home = expand_home(str, sh);
//         if (!home)
//             return (NULL);
//         return (home);
//     }
//     env = sh->env;
//     if (!init_expand(&exp, str, sh->status))
//         return (NULL);
//     while (exp.str[exp.i])
//     {
//         if (exp.str[exp.i] == '\'')
//             handle_single_quote(&exp);
//         else if (exp.str[exp.i] == '\"')
//         {
//             if (!handle_double_quote(&exp, env))
//                 return (handle_expand_error(&exp, out_type, error_char));
//         }
//         else if (exp.str[exp.i] == '$' && !exp.in_squote)
//         {
//             if (!handle_dollar(exp.str, &exp, env))
//                 return (handle_expand_error(&exp, out_type, error_char));
//         }
//         else
//         {
//             if (!append_char(&exp, exp.str[exp.i++]))
//                 return (handle_expand_error(&exp, out_type, error_char));
//         }
//     }
//     exp.buf[exp.len] = '\0';
//     result = ft_strdup(exp.buf);
//     if (!result)
//         return (free_expansion(&exp), NULL);
//     if (out_type)
//         *out_type = exp.illegal_type;
//     if (error_char && exp.error_char)
//         *error_char = exp.error_char[0];
//     free_expansion(&exp);
//     return (result);
// }

static char *handle_home_expansion_if_needed(char *str, t_shell *sh)
{
	if (str && str[0] == '~' && (!str[1] || str[1] == '/'))
		return (expand_home(str, sh));
	return (NULL);
}

static int process_expansion_loop(t_expansion *exp, t_env *env, t_suffix_type *out_type, char *error_char)
{
    while (exp->str[exp->i])
    {
        if (exp->str[exp->i] == '\'')
            handle_single_quote(exp);
        else if (exp->str[exp->i] == '\"')
        {
            if (!handle_double_quote(exp, env))
                return (handle_expand_error(exp, out_type, error_char), 0);
        }
        else if (exp->str[exp->i] == '$' && !exp->in_squote)
        {
            if (!handle_dollar(exp->str, exp, env))
                return (handle_expand_error(exp, out_type, error_char), 0);
        }
        else
        {
            if (!append_char(exp, exp->str[exp->i++]))
                return (handle_expand_error(exp, out_type, error_char), 0);
        }
    }
    return (1);
}

static char *finalize_expansion_result(t_expansion *exp, t_suffix_type *out_type, char *error_char)
{
	char *result;
    
    result = ft_strdup(exp->buf);
	if (!result)
	{
		free_expansion(exp);
		return (NULL);
	}
	if (out_type)
		*out_type = exp->illegal_type;
	if (error_char && exp->error_char)
		*error_char = exp->error_char[0];
	free_expansion(exp);
	return (result);
}

char *expand_string(char *str, t_shell *sh, t_suffix_type *out_type, char *error_char)
{
	t_expansion exp;
	char *result;
	t_env *env;
	char *home;

	if (!str)
		return (NULL);
	home = handle_home_expansion_if_needed(str, sh);
	if (home)
		return (home);
	env = sh->env;
	if (!init_expand(&exp, str, sh->status))
		return (NULL);
	if (!process_expansion_loop(&exp, env, out_type, error_char))
		return (NULL);
	result = finalize_expansion_result(&exp, out_type, error_char);
	return (result);
}
