/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:43:37 by jdu               #+#    #+#             */
/*   Updated: 2025/07/01 21:37:26 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_shell_env(t_shell *sh, char **envp)
{
	char	*de;

	sh->env = init_env(envp);
	if (!sh->env)
		return (free(sh), 0);
	handle_empty_env(&sh->env);
	if (!sh->env)
		return (free(sh), 0);
	sh->username = extract_username(sh->env);
	if (!sh->username)
		return (free_env(sh->env), free(sh), 0);
	sh->paths = init_path_array(sh->env);
	de = get_env_var_value(sh, "HOME");
	if (de)
		sh->default_home = ft_strdup(de);
	else
		sh->default_home = ft_strdup("/tmp");
	if (!sh->paths || !sh->default_home)
	{
		free(sh->username);
		free_env(sh->env);
		free(sh);
		return (0);
	}
	return (1);
}

static void	init_shell_fields(t_shell *sh)
{
	sh->trimmed_prompt = NULL;
	sh->status = 0;
	sh->old_pipe.fd[0] = -1;
	sh->old_pipe.fd[1] = -1;
	sh->new_pipe.fd[0] = -1;
	sh->new_pipe.fd[1] = -1;
	sh->cmd = NULL;
	sh->token_list = NULL;
	sh->curr_cmd = NULL;
	sh->should_expand = 0;
}

t_shell	*init_shell(char **envp)
{
	t_shell	*sh;

	sh = malloc(sizeof(t_shell));
	if (!sh)
		return (NULL);
	if (!init_shell_env(sh, envp))
		return (NULL);
	init_shell_fields(sh);
	return (sh);
}

static void	free_shell_env(t_shell *sh)
{
	free_env(sh->env);
	sh->env = NULL;
	free_paths(sh->paths);
	sh->paths = NULL;
	if (sh->username)
	{
		free(sh->username);
		sh->username = NULL;
	}
	if (sh->default_home)
	{
		free(sh->default_home);
		sh->default_home = NULL;
	}
	if (sh->trimmed_prompt)
	{
		free(sh->trimmed_prompt);
		sh->trimmed_prompt = NULL;
	}
}

void	free_shell(t_shell *sh)
{
	if (!sh)
		return ;
	free_shell_env(sh);
	if (sh->token_list)
	{
		free_tokens(sh->token_list);
		sh->token_list = NULL;
	}
	if (sh->cmd)
	{
		free_cmd_list(sh->cmd);
		sh->cmd = NULL;
		sh->curr_cmd = NULL;
	}
	free(sh);
}
