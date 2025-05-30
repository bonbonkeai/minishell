#include "minishell.h"

int	is_red_type(t_token_type type)
{
	return (type == T_INPUT || type == T_OUTPUT
		|| type == T_APPEND || type == T_HEREDOC);
}

