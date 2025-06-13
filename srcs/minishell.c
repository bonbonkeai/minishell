#include "minishell.h"

/* static void print_cmd_list(t_cmd *cmd_list)
{
    while (cmd_list)
    {
        if (cmd_list->cmd)
            printf("cmd is: %s\n", cmd_list->cmd);
        else
            printf("no cmd infile: (null)\n");
        cmd_list = cmd_list->next;
    }
} */

void	process_input(t_shell *shell, char *input)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	shell->trimmed_prompt = ft_strtrim(input, " \t\n");
	if (!shell->trimmed_prompt || shell->trimmed_prompt[0] == '\0')
		return ;
	if (!lexer(shell))
		return ;
	tokens = tokenize_prompt(shell->trimmed_prompt);
	if (!tokens)
		return ;
	if (check_token_syntax(tokens))
	{
		free_tokens(tokens);
		return ;
	}
	// expand_tokens(tokens, shell->env, shell->status);
	cmd_list = parser(tokens);
	if (cmd_list)
	{
		//print_cmd_list(cmd_list);
		executor(cmd_list, shell);
		//exec_simple(cmd_list, shell->env);
		free_cmd_list(cmd_list);
	}
	free_tokens(tokens);
}

void minishell_loop(t_shell *shell)
{
	char *line;
	char *prompt;

	while (1)
	{
		//signal_hiding();
		prompt = build_prompt(shell);
		//line = readline("minishell$ ");
		line = readline(prompt);
		free(prompt);
		if (!line)
			break;
		if (line[0])
			add_history(line);
/* 		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		} */
		process_input(shell, line);
		free(line);
		free(shell->trimmed_prompt);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);
	//signal_handle();
	if (argc > 1)
	{
		process_input(shell, argv[1]);
		free(shell->trimmed_prompt);
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


