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

// void expand_tab(char **tab, t_env *env_head, int status)
// {
//     int i;
//     char *expanded;

//     if (!tab || !env_head)
//         return ;
//     i = 0;
//     while (tab[i])
//     {
//         expanded = expand_string((tab[i]), env_head, status);
//         if (!expanded)
//         {
//             i++;
//             continue ;
//         }
//         // free(tab[i]);
//         tab[i] = expanded;
//         i++;
//     }
// }

int expand_tab(char **tab, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
{
    int i;
    char *expanded;
    t_suffix_type type;

    if (!tab || !env_head)
        return (1);
    i = 0;
    while (tab[i])
    {
        expanded = expand_string(tab[i], env_head, status, &type, error_char);
        if (!expanded)
        {
            if (type != SUFFIX_OK)
                *out_type = type;
            return (0);
        }
        tab[i] = expanded;
        i++;
    }
    return (1);
}

int expand_single(char **str, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
{
    char *tmp[2];
    int expand_status;

    if (!str || !*str)
        return (1);
    tmp[0] = *str;
    tmp[1] = NULL;
    expand_status = expand_tab(tmp, env_head, status, out_type, error_char);
    *str = ft_strdup(tmp[0]);
    if (!*str)
        return (1);
    return (expand_status);
}


// void expand_single(char **str, t_env *env_head, int status)
// {
//     if (!str || !*str)
//         return;

//     char *tmp[2];
//     tmp[0] = *str;
//     tmp[1] = NULL;

//     expand_tab(tmp, env_head, status);
//     *str = tmp[0];
// }


// void expand_all(t_cmd *cmds, t_env *env_head, int status)
// {
//     if (!cmds)
//         return;
//     while (cmds)
//     {
//         expand_tab(cmds->args, env_head, status);
//         expand_single(&cmds->cmd, env_head, status);
//         expand_tab(cmds->red, env_head, status);
//         cmds = cmds->next;
//     }
// }

// int expand_all(t_cmd *cmds, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
// {
//     while (cmds)
//     {
//         if (!expand_tab(cmds->args, env_head, status, out_type, error_char))
//             return (0);
//         if (!expand_single(&cmds->cmd, env_head, status, out_type, error_char))
//             return (0);
//         if (!expand_tab(cmds->red, env_head, status, out_type, error_char))
//             return (0);
//         cmds = cmds->next;
//     }
//     return (1);
// }

int expand_vars(t_cmd *cmds, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
{
    while (cmds)
    {
        if (!expand_tab(cmds->args, env_head, status, out_type, error_char))
            return (0);
        if (!expand_single(&cmds->cmd, env_head, status, out_type, error_char))
            return (0);
        if (!expand_tab(cmds->red, env_head, status, out_type, error_char))
            return (0);
        cmds = cmds->next;
    }
    return (1);
}

// int expand_vars(t_cmd *cmds, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
// {
// 	char **merged_args;

// 	while (cmds)
// 	{
// 		// 展开参数数组
// 		if (!expand_tab(cmds->args, env_head, status, out_type, error_char))
// 			return (0);

// 		// 合并参数数组为单一 arg 列表（例如 echo 'a'"b"c → abc）
// 		merged_args = merge_args(cmds->args);
// 		if (!merged_args)
// 			return (0);
// 		free_paths(cmds->args);
// 		cmds->args = merged_args;
//         if (cmds->cmd)
//             free(cmds->cmd);
//         cmds->cmd = ft_strdup(cmds->args[0]);
//         if (!cmds->cmd)
//             return (0);

// 		// 展开命令名称
// 		if (!expand_single(&cmds->cmd, env_head, status, out_type, error_char))
// 			return (0);

// 		// 展开重定向符
// 		if (!expand_tab(cmds->red, env_head, status, out_type, error_char))
// 			return (0);

// 		cmds = cmds->next;
// 	}
// 	return (1);
// }


int expand_all(t_cmd *cmds, t_env *env_head, int status, t_suffix_type *out_type, char *error_char)
{
    if (!expand_vars(cmds, env_head, status, out_type, error_char))
        return (0);
    if (expand_heredoc_in_cmd_list(cmds, env_head, status))
        return (0);
    return (1);
}

char *expand_string(char *str, t_env *lst_env, int status, t_suffix_type *out_type, char *error_char)
{
    t_expansion exp;
    char *home; 
    char *rest; 
    char *joined;
    char *result;

    if (!str)
        return (NULL);
    if (str[0] == '~' && (!str[1] || str[1] == '/'))
    {
        home = get_env_value(lst_env, "HOME");
        if (!home)
            return (ft_strdup(str));
        rest = ft_strdup(str + 1);
        if (!rest)
            return (NULL);
        joined = ft_strjoin(home, rest);
        free(rest);
        free(str);
        return (joined);
    }
    if (!init_expand(&exp))
        return (NULL);
    exp.str = str;
    exp.status = status;
    exp.exit_status = ft_itoa(status);
    exp.illegal_type = SUFFIX_OK;
    while (exp.str[exp.i])
    {
        if (exp.str[exp.i] == '\'')
            handle_single_quote(&exp);
        else if (exp.str[exp.i] == '\"')
            handle_double_quote(&exp, lst_env);
        else if (exp.str[exp.i] == '$' && !exp.in_dquote)
        {
            if (!handle_dollar(exp.str, &exp, lst_env))
            {
                if (out_type)
                    *out_type = exp.illegal_type;
                if (error_char && exp.error_char)
                    *error_char = exp.error_char[0];
                else if (error_char)
                    *error_char = '\0';
                free(exp.buf);
                free(exp.exit_status);
                free(exp.error_char);
                return (NULL);
            }
        }
        else
        {
            if (!append_char(&exp, exp.str[exp.i]))
            {
                if (out_type)
                    *out_type = SUFFIX_SYNTAX_ERROR;
                free(exp.buf);
                free(exp.exit_status);
                return (NULL);
            }
            exp.i++;
        }
    }
    exp.buf[exp.len] = '\0';
    result = ft_strdup(exp.buf);
    if (out_type)
        *out_type = exp.illegal_type;
    if (exp.error_char)
        *error_char = exp.error_char[0];
    free(exp.buf);
    free(exp.exit_status);
    free(exp.error_char);
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
	// else if (type == SUFFIX_PIPE)
	// 	ft_fprintf(2, "minishell: `%c': command not found(pipe misused)\n", ch);
	// else if (type == SUFFIX_REDIR)
    // {
    //     if (ch == '>')
	// 	{
    //         ft_fprintf(2, "minishell: syntax error near unexpected token `>'\n");
    //         return (1);
    //     }
	//     else if (ch == '<')
	// 	    return (0);
    // }
	else if (type == SUFFIX_SEMICOLON)
		ft_fprintf(2, "minishell: command not found(unexpected `;')\n");
	else
		return (0);
	return (1);
}


