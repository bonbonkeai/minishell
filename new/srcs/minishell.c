/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:32 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:47:34 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *safe_prompt(t_shell *shell)
{
    char *prompt;
    
    prompt = build_prompt(shell);
    if (!prompt)
        prompt = ft_strdup("minishell$ ");
    return (prompt);
}

static void cleanup_and_exit(t_shell *sh, int error_status)
{
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    if (sh->cmd)
    { 
        free_cmd_list(sh->cmd);
        sh->cmd = NULL;
    }
    sh->curr_cmd = NULL;
    if (sh->trimmed_prompt)
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
    }
    sh->status = error_status;
}

void process_input(t_shell *sh, char *input)
{
    t_suffix_type illegal_type;
    char error_char;
    t_cmd *cmd;

    illegal_type = SUFFIX_OK;
    error_char = 0;
    sh->trimmed_prompt = ft_strtrim(input, " \t\n");
    if (!sh->trimmed_prompt || sh->trimmed_prompt[0] == '\0')
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
        return ;
    }
    if (!lexer(sh))
    {
        // printf("[process_input] lexer 错误\n");
        return (cleanup_and_exit(sh, 2));
    }
    if (sh->token_list)
    {
        free_tokens(sh->token_list);
        sh->token_list = NULL;
    }
    tokenize_prompt(sh, sh->trimmed_prompt);
    if (!sh->token_list)
    {
        // printf("[process_input] tokenize_prompt 失败\n");
        return (cleanup_and_exit(sh, 2));
    }
    // if (check_token_syntax(tokens))
    if (check_token_syntax(sh->token_list))
    {
        // printf("[process_input] 语法错误\n");
        return (cleanup_and_exit(sh, 2));
    }
    cmd = sh->cmd;
    // cmd = parser(tokens);
    // cmd = parser(sh->token_list);
    cmd = parser(sh);
    if (!cmd)
    {
        // printf("[process_input] parser 返回 NULL\n");
        return (cleanup_and_exit(sh, 2));
    }
    sh->cmd = cmd;
    // printf("[process_input] parser 成功, sh->cmd 地址: %p\n", (void *)sh->cmd);
    if (!expand_all(sh, &illegal_type, &error_char))
    {
        // printf("[process_input] expand_all 失败\n");
        has_illegal_expansion(illegal_type, error_char);
        // free_cmd_list(cmd);
        return (cleanup_and_exit(sh, 2));
    }
    //
    sh->curr_cmd = sh->cmd;
    //
    if (sh->cmd)
    {
        // printf("[process_input] 开始执行命令\n");
        // ft_fprintf(1, "%s\n", sh->cmd->cmd);
        sh->status = executor(sh);
    }
    cleanup_and_exit(sh, sh->status);
}

void minishell_loop(t_shell *shell)
{
	char *line;
    char *prompt;

	while (1)
	{
        prompt = safe_prompt(shell);
        if (!prompt)
        {
            write(2, "Error: failed to allocate prompt\n", 33);
            break ;
        }
        line = readline(prompt);
        free(prompt);
		if (!line)
        {
            write(1, "exit\n", 5);     
            break ;
        }
		if (line[0])
			add_history(line);
        if (ft_strncmp(line, "exit", 4) == 0 && (line[4] == '\0' || ft_isspace(line[4])))
		{
			free(line);
			break ;
		}
		process_input(shell, line);
		free(line);
	}
}

static char	*ft_join_argv(int argc, char **argv)
{
	int		i;
	char	*joined;
	char	*tmp;
	char	*with_space;

	i = 0;
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (i < argc)
	{
		tmp = ft_strjoin(joined, argv[i]);
		free(joined);
		if (!tmp)
			return (NULL);
		if (i < argc - 1)
		{
			with_space = ft_strjoin(tmp, " ");
			free(tmp);
			if (!with_space)
				return (NULL);
			joined = with_space;
		}
		else
			joined = tmp;
		i++;
	}
	return (joined);
}


int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
    char *input;

	shell = init_shell(envp);
	if (!shell)
    {
         write(2, "Error: failed to initialize shell\n", 34);
		return (EXIT_FAILURE);
    }
    // signal_handle();
	if (argc > 1)
	{
        input = ft_join_argv(argc - 1, argv + 1);
		if (!input)
		{
			write(2, "Error: failed to join input args\n", 33);
			free_shell(shell);
			return (EXIT_FAILURE);
		}
		process_input(shell, input);
		free(input);
		free_shell(shell);
		return (EXIT_SUCCESS);
	}
	else
	{
		minishell_loop(shell);
		free_shell(shell);
		return (EXIT_SUCCESS);
	}
}


