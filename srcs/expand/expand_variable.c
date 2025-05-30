#include "minishell.h"

int	handle_dollar(char *input, t_expansion *exp, t_env *lst_env, int status)
{
	exp->i++;
	if (input[exp->i] == '?')
		return handle_exit_status(exp, status);
	else if (ft_isdigit(input[exp->i]))
	{
		exp->i++;
		return (1);
	}
	else if (input[exp->i] == '{')
		return (handle_braces(input, exp, lst_env, status));
	else if (ft_isalnum(input[exp->i]) || input[exp->i] == '_')
		return (handle_variable(input, exp, lst_env));
	else
	{
		exp->result[exp->len++] = '$';
		return (1);
	}
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
	return (append_str(exp)); // malformed ${}
}

int handle_exit_status(t_expansion *exp, int status)
{
    exp->i++;
    exp->exit_status = ft_itoa(status);
    if (!exp->exit_status || !append_str(exp))
        return (0);
    return (1);
}

int handle_env_var(t_expansion *exp, t_env *lst_env)
{
    exp->env_val = mini_get_env(exp->var_name, lst_env);
    if (!exp->env_val || !append_env(exp))
        return (0);
    return (1);
}

int valid_exp(int c)
{
    if (c == '?' || c == '{' || ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}





