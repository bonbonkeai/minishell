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


int expand_tab(char **tab, t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    int i;
    char *expanded;
    t_suffix_type type;

    if (!tab || !sh->env || !sh || !sh->cmd)
        return (1);
    i = 0;
    while (tab[i])
    {
        // printf("[expand_tab] before: %s\n", tab[i]);
        expanded = expand_string(tab[i], sh, &type, error_char);
        // printf("[expand_tab] after: %s\n", expanded);
        if (!expanded)
        {
            if (type != SUFFIX_OK)
                *out_type = type;
            return (0);
        }
        free(tab[i]);
        tab[i] = expanded;
        i++;
    }
    return (1);
}

// int expand_single(char **str, t_shell *sh, t_suffix_type *out_type, char *error_char)
// {
//     char *tmp[2];
//     int expand_status;
//     char *expanded;

//     if (!str || !*str)
//         return (1);
//     tmp[0] = *str;
//     tmp[1] = NULL;
//     expand_status = expand_tab(tmp, sh, out_type, error_char);
//     if (expand_status)
//         return (1);
//     expanded = ft_strdup(tmp[0]);
//     if (!expanded)
//         return (1);
//     free(*str);
//     *str = expanded;
//     return (0);
//     // return (expand_status);
// }

// int expand_single(char **str, t_shell *sh, t_suffix_type *out_type, char *error_char)
// {
//     char *expanded;

//     if (!str || !*str)
//         return (1);
//     expanded = expand_string(*str, sh, out_type, error_char);
//     if (!expanded)
//         return (0);
//     free(*str);
//     *str = expanded;
//     return (1);
// }

int expand_single(char **str, t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    char *tmp[2];

    if (!str || !*str)
        return (1);
    tmp[0] = *str;
    tmp[1] = NULL;
    if (!expand_tab(tmp, sh, out_type, error_char))
        return (0);
    *str = tmp[0];
    return (1);
}

int expand_vars(t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    t_cmd *cmd;

    cmd = sh->cmd;
    while (cmd)
    {
        // printf("CMD: \n");
        // for (int i = 0; cmd->args && cmd->args[i]; i++)
        // printf("  raw arg[%d]: '%s'\n", i, cmd->args[i]);
        if (!expand_tab(cmd->args, sh, out_type, error_char))
            return (0);
        if (cmd->args && cmd->args[0])
        {
            if (!expand_single(&cmd->args[0], sh, out_type, error_char))
                return (0);
        }
        if (!expand_tab(cmd->red, sh, out_type, error_char))
            return (0);
        cmd = cmd->next;
    }
    return (1);
}


int expand_all(t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    t_cmd *cmd;

    if (!expand_vars(sh, out_type, error_char))
        return (0);
    if (expand_heredoc_in_cmd_list(sh))
        return (0);
    cmd = sh->cmd;
    while (cmd)
    {
        if (cmd->args && cmd->args[0])
        {
            free(cmd->cmd);
            cmd->cmd = ft_strdup(cmd->args[0]);
            if (!cmd->cmd)
                return (0);
        }
        cmd = cmd->next;
    }
    return (1);
}

// char *expand_string(char *str, t_env *lst_env, int status, t_suffix_type *out_type, char *error_char)
// {
//     t_expansion exp;
//     char *home; 
//     char *rest; 
//     char *joined;
//     char *result;

//     if (!str)
//         return (NULL);
//     if (str[0] == '~' && (!str[1] || str[1] == '/'))
//     {
//         home = get_env_value(lst_env, "HOME");
//         if (!home)
//             return (ft_strdup(str));
//         rest = ft_strdup(str + 1);
//         if (!rest)
//             return (NULL);
//         joined = ft_strjoin(home, rest);
//         free(rest);
//         free(str);
//         return (joined);
//     }
//     if (!init_expand(&exp))
//         return (NULL);
//     exp.str = str;
//     exp.status = status;
//     exp.exit_status = ft_itoa(status);
//     exp.illegal_type = SUFFIX_OK;
//     while (exp.str[exp.i])
//     {
//         if (exp.str[exp.i] == '\'')
//             handle_single_quote(&exp);
//         else if (exp.str[exp.i] == '\"')
//             handle_double_quote(&exp, lst_env);
//         else if (exp.str[exp.i] == '$' && !exp.in_dquote)
//         {
//             if (!handle_dollar(exp.str, &exp, lst_env))
//             {
//                 if (out_type)
//                     *out_type = exp.illegal_type;
//                 if (error_char && exp.error_char)
//                     *error_char = exp.error_char[0];
//                 else if (error_char)
//                     *error_char = '\0';
//                 free(exp.buf);
//                 free(exp.exit_status);
//                 free(exp.error_char);
//                 return (NULL);
//             }
//         }
//         else
//         {
//             if (!append_char(&exp, exp.str[exp.i]))
//             {
//                 if (out_type)
//                     *out_type = SUFFIX_SYNTAX_ERROR;
//                 free(exp.buf);
//                 free(exp.exit_status);
//                 return (NULL);
//             }
//             exp.i++;
//         }
//     }
//     exp.buf[exp.len] = '\0';
//     result = ft_strdup(exp.buf);
//     if (out_type)
//         *out_type = exp.illegal_type;
//     if (exp.error_char)
//         *error_char = exp.error_char[0];
//     free(exp.buf);
//     free(exp.exit_status);
//     free(exp.error_char);
//     return (result);
// }


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

char *handle_expand_error(t_expansion *exp, t_suffix_type *out_type, char *error_char)
{
	if (out_type)
		*out_type = exp->illegal_type;

	if (error_char)
	{
		if (exp->error_char)
			*error_char = exp->error_char[0];
		else
			*error_char = '\0';
	}

	free_expansion(exp);
	return (NULL);
}

// char *expand_string(char *str, t_shell *sh, t_suffix_type *out_type, char *error_char)
// {
//     t_expansion exp;
//     char *result;

//     if (!str)
//         return (NULL);
//     if (str[0] == '~' && (!str[1] || str[1] == '/'))
//         return (expand_home(str, sh));
//     if (!init_expand(&exp))
//         return (NULL);
//     exp.str = str;
//     exp.status = status;
//     exp.exit_status = ft_itoa(status);
//     exp.illegal_type = SUFFIX_OK;
//     while (exp.str[exp.i])
//     {
//         if (exp.str[exp.i] == '\'')
//             handle_single_quote(&exp);
//         else if (exp.str[exp.i] == '\"')
//             handle_double_quote(&exp, lst_env);
//         else if (exp.str[exp.i] == '$' && !exp.in_dquote)
//         {

//             else if (exp.str[exp.i] == '$' && !exp.in_squote)
//             {
//                 if (!handle_dollar(&exp, sh->env))
//                     return (handle_expand_error(&exp, out_type, error_char));
//             }
//             else
//             {
//                 if (!append_char(&exp, exp.str[exp.i++]))
//                     return (handle_expand_error(&exp, out_type, error_char));
//             }
//         }
//     }
//     exp.buf[exp.len] = '\0';
//     result = ft_strdup(exp.buf);
//     if (out_type)
//         *out_type = exp.illegal_type;
//     if (exp.error_char)
//         *error_char = exp.error_char[0];
//     free_expansion(&exp);
//     return (result);
// }

char *expand_string(char *str, t_shell *sh, t_suffix_type *out_type, char *error_char)
{
    t_expansion exp;
    char *result;
    t_env *env;

    if (!str)
        return (NULL);
    if (str[0] == '~' && (!str[1] || str[1] == '/'))
    // {
    //     char *res = expand_home(str, sh);
    //     printf("[expand_string] ~ expanded to: %s\n", res);
    //     return res;
    // }
        return (expand_home(str, sh));
    env = sh->env;
    if (!init_expand(&exp, str, sh->status))
        return (NULL);
    while (exp.str[exp.i])
    {
        if (exp.str[exp.i] == '\'')
            handle_single_quote(&exp);
        else if (exp.str[exp.i] == '\"')
        {
            if (!handle_double_quote(&exp, env))
                return (handle_expand_error(&exp, out_type, error_char));
        }
        else if (exp.str[exp.i] == '$' && !exp.in_squote)
        {
            if (!handle_dollar(exp.str, &exp, env))
                return (handle_expand_error(&exp, out_type, error_char));
        }
        else
        {
            if (!append_char(&exp, exp.str[exp.i++]))
                return (handle_expand_error(&exp, out_type, error_char));
        }
    }
    exp.buf[exp.len] = '\0';
    result = ft_strdup(exp.buf);
    if (!result)
        return (free_expansion(&exp), NULL);
    if (out_type)
        *out_type = exp.illegal_type;
    if (error_char && exp.error_char)
        *error_char = exp.error_char[0];
    free_expansion(&exp);
    return (result);
}



int has_illegal_expansion(t_suffix_type type, char ch)
{
	if (type == SUFFIX_SYNTAX_ERROR)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", ch);
	else if (type == SUFFIX_HISTORY)
		ft_fprintf(2, "minishell: !%c: event not found\n", ch);
	else if (type == SUFFIX_BACKGROUND)
		ft_fprintf(2, "minishell: `%c': command not found\n", ch);
	else if (type == SUFFIX_SEMICOLON)
		ft_fprintf(2, "minishell: command not found(unexpected `;')\n");
	else
		return (0);
	return (1);
}


