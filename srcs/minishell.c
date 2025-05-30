#include "minishell.h"

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
		// executor(cmd_list);
		free_cmd_list(cmd_list);
	}
	free_tokens(tokens);
}

void minishell_loop(t_shell *shell)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (line[0])
			add_history(line);
		if (ft_strcmp(line, "exit") == 0)
		{
			free(line);
			break ;
		}
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


