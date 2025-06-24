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

static void cleanup_and_exit(t_shell *sh, t_token *tokens, int error_status)
{
    if (tokens)
        free_tokens(tokens);
    if (sh->cmd)
    {
        // printf("[cleanup_and_exit] 正在释放 sh->cmd: %p\n", (void *)sh->cmd);
        free_cmd_list(sh->cmd);
        sh->cmd = NULL;
        // printf("[cleanup_and_exit] sh->cmd 已设置为 NULL\n");
    }
    // else
    //     printf("[cleanup_and_exit] sh->cmd 已为 NULL, 无需释放\n");
    if (sh->trimmed_prompt)
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
    }
    sh->status = error_status;
}

void process_input(t_shell *sh, char *input)
{
    t_token *tokens;
    t_suffix_type illegal_type;
    char error_char;
    t_cmd *cmd;
    
    tokens = NULL;
    illegal_type = SUFFIX_OK;
    error_char = 0;
    cmd = NULL;
    // printf("[process_input] 原始输入: \"%s\"\n", input);
    sh->trimmed_prompt = ft_strtrim(input, " \t\n");
    if (!sh->trimmed_prompt || sh->trimmed_prompt[0] == '\0')
    {
        free(sh->trimmed_prompt);
        sh->trimmed_prompt = NULL;
        return;
    }
    // printf("[process_input] 清理后的输入: \"%s\"\n", sh->trimmed_prompt);
    if (!lexer(sh))
    {
        // printf("[process_input] lexer 错误\n");
        return (cleanup_and_exit(sh, NULL, 2));
    }
    tokens = tokenize_prompt(sh->trimmed_prompt);
    if (!tokens)
    {
        // printf("[process_input] tokenize_prompt 失败\n");
        return (cleanup_and_exit(sh, NULL, 2));
    }
    if (check_token_syntax(tokens))
    {
        // printf("[process_input] 语法错误\n");
        return (cleanup_and_exit(sh, tokens, 2));
    }
    cmd = parser(tokens);
    if (!cmd)
    {
        // printf("[process_input] parser 返回 NULL\n");
        return (cleanup_and_exit(sh, tokens, 2));
    }
    sh->cmd = cmd;
    // printf("[process_input] parser 成功, sh->cmd 地址: %p\n", (void *)sh->cmd);
    if (!expand_all(sh, &illegal_type, &error_char))
    {
        // printf("[process_input] expand_all 失败\n");
        has_illegal_expansion(illegal_type, error_char);
        // free_cmd_list(cmd);
        return (cleanup_and_exit(sh, tokens, 2));
    }
    if (sh->cmd)
    {
        // printf("[process_input] 开始执行命令\n");
        sh->status = executor(sh);
    }
    // else
	// {
	// 	printf("[process_input] sh->cmd 在执行前被置 NULL\n");
	// }
    // printf("[process_input] 命令执行完成, status = %d\n", sh->status);
    cleanup_and_exit(sh, tokens, sh->status);
    // sh->cmd = NULL;
    free(sh->trimmed_prompt);
    sh->trimmed_prompt = NULL;
}

// void    process_input(t_shell *shell, char *input)
// {
//     t_token *tokens;
//     t_cmd *tmp;
//     int i;
//     t_suffix_type illegal_type;
//     char error_char;
//     int status;

//     shell->trimmed_prompt = ft_strtrim(input, " \t\n");
//     if (!shell->trimmed_prompt || shell->trimmed_prompt[0] == '\0')
//         return ;
//     if (!lexer(shell))
//     {
//         shell->status = 2;
//         return ;
//     }
//     tokens = tokenize_prompt(shell->trimmed_prompt);
//     if (!tokens)
//     {
//         shell->status = 2;
//         return ;
//     }
//     if (check_token_syntax(tokens))
//     {
//         free_tokens(tokens);
//         shell->status = 2;
//         return ;
//     }
//     shell->cmd = parser(tokens, shell);
//     if (!shell->cmd)
//     {
//         free_tokens(tokens);
//         shell->status = 2;
//         return ;
//     }
//     illegal_type = SUFFIX_OK;
//     error_char = 0;
//     if (!expand_all(shell, &illegal_type, &error_char))
//     {
//         has_illegal_expansion(illegal_type, error_char);
//         free_tokens(tokens);
//         shell->status = 2;
//         return ;
//     }
//     tmp = shell->cmd;
//     i = 0;
//     while (tmp)
//     {
//         printf("Command %d: %s\n", i, tmp->cmd ? tmp->cmd : "(null)");

//         if (tmp->args)
//         {
//             int j = 0;
//             while (tmp->args[j])
//             {
//                 printf("  Arg[%d]: %s\n", j, tmp->args[j]);
//                 j++;
//             }
//         }
//         tmp = tmp->next;
//         i++;
//     }
//     if (shell->cmd)
// 	{
//         status = executor(shell);
//         shell->status = status;
// 	}
//     // free_cmd_list(cmd_list);
//     // free_cmd_list(shell->cmd);
//     // free_shell(shell);
//     free_tokens(tokens);
// }

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
        // if (shell->cmd)
		// 	printf("[minishell_loop] cleaning up sh->cmd at %p\n", (void *)shell->cmd);
		// else
		// 	printf("[minishell_loop] sh->cmd 已经在内部释放\n");
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
		// process_input(shell, argv[1]);
		// // free(shell->trimmed_prompt);
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


