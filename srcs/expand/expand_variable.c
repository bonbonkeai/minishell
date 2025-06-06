#include "minishell.h"

int handle_dollar(char *input, t_expansion *exp, t_env *lst_env, int status)
{
    char *key;
    char *value;
    int matched_len;
    char next;
    t_suffix_type type;

    key = NULL;
    value = NULL;
    matched_len = 0;
    exp->i++;
    if (input[exp->i] == '?')
        return handle_exit_status(exp, status);
    if (ft_isdigit(input[exp->i]))
    {
        exp->i++;
        return (1);
    }
    if (input[exp->i] == '{')
        return (handle_braces(exp, lst_env));
    // key = extract_var_name(input, exp->i, lst_env, &matched_len);
    key = extract_var_name(input, exp->i, &matched_len);
    // if (key)
    // {
    //     value = get_env_value(lst_env, key);
    //     exp->i += matched_len;
    //     free(key);
    //     if (value && !append_str_to_buffer(exp, value))
    //         return (0);
    //     return (1);
    // }
    if (key)
	{
		value = get_env_value(lst_env, key);
		next = input[exp->i + matched_len];
		type = get_suffix_type(next);
		// if (type == SUFFIX_SYNTAX_ERROR)
		// {
		// 	ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", next);
		// 	free(key);
		// 	return (0);
		// }
		// else if (type == SUFFIX_HISTORY)
		// {
		// 	ft_fprintf(2, "minishell: !%s: event not found\n", input + exp->i + matched_len + 1);
		// 	free(key);
		// 	return (0);
		// }
        if (type != SUFFIX_OK)
		{
			exp->illegal_type = type;
            if (exp->error_char)
		        free(exp->error_char);
            exp->error_char = ft_substr(input, exp->i + matched_len, 1);
			free(key);
			return (0);
		}
		if (value && !append_str_to_buffer(exp, value))
		{
			free(key);
			return (0);
		}
		exp->i += matched_len;
		free(key);
		return (1);
	}
    // if (key)
    // {
    //     value = get_env_value(lst_env, key);
    //     if (value && !append_str_to_buffer(exp, value))
    //     {
    //         free(key);
    //         return (0);
    //     }
    //     exp->i += matched_len;
    //     free(key);
    //     return (1);
    // }
    if (!append_char(exp, '$'))
        return (0);
    if (input[exp->i])
    {
        if (!append_char(exp, input[exp->i]))
            return (0);
        exp->i++;
    }
    return (1);
}

int	handle_braces(t_expansion *exp, t_env *lst_env)
{
	int		start;
	int		end;

	start = ++exp->i;
	while (exp->str[exp->i] && exp->str[exp->i] != '}')
		exp->i++;
	end = exp->i;
	if (exp->str[exp->i] == '}')
		exp->i++;
	if (end > start)
	{
		exp->var_name = ft_substr(exp->str, start, end - start);
		if (!exp->var_name)
			return (0);
		return (handle_env_var(exp, lst_env));
	}
	return (1);
}

// char *extract_var_name(const char *input, int start, t_env *env, int *matched_len)
// {
//     int l;
//     char *key;
//     char *value;

//     l = 0;
//     key = NULL;
//     value = NULL;
//     if (!ft_isalpha(input[start]) && input[start] != '_')
//     {
//         *matched_len = 0;
//         return (NULL);
//     }
//     while (ft_isalnum(input[start + l]) || input[start + l] == '_')
//         l++;
//     while (l > 0)
//     {
//         key = ft_substr(input, start, l);
//         if (!key)
//             return (NULL);
//         value = get_env_value(env, key);
//         if (value)
//         {
//             *matched_len = l;
//             return (key);
//         }
//         free(key);
//         l--;
//     }
//     l = 0;
//     while (ft_isalnum(input[start + l]) || input[start + l] == '_')
//         l++;
//     if (l > 0)
//     {
//         *matched_len = l;
//         return (ft_substr(input, start, l));
//     }
//     *matched_len = 0;
//     return (NULL);
// }

char *extract_var_name(const char *input, int start, int *matched_len)
{
    int l;

    l = 0;
    if (!ft_isalpha(input[start]) && input[start] != '_')
    {
        *matched_len = 0;
        return (NULL);
    }
    while (ft_isalnum(input[start + l]) || input[start + l] == '_')
        l++;
    *matched_len = l;
    return ft_substr(input, start, l);
}

int append_str_to_buffer(t_expansion *exp, const char *str)
{
    int i;
	
	i = 0;
    while (str[i])
    {
        if (!append_char(exp, str[i]))
            return (0);
        i++;
    }
    return (1);
}

t_suffix_type get_suffix_type(char c)
{
    if (c == '|')
        return (SUFFIX_PIPE);
    else if (c == '>' || c == '<')
        return (SUFFIX_REDIR);
    else if (c == '(' || c == ')' || c == '`')
        return (SUFFIX_SYNTAX_ERROR);
    else if (c == '!')
        return (SUFFIX_HISTORY);
    else if (c == '&')
        return (SUFFIX_BACKGROUND);
    else if (c == ';')
        return (SUFFIX_SEMICOLON);
    else
        return (SUFFIX_OK);
}
