#include "minishell.h"

// static void print_cmd_list(t_cmd *cmd_list)
// {
//     while (cmd_list)
//     {
//         if (cmd_list->infile)
//             printf("cmd IN FILE: %s\n", cmd_list->infile);
//         else
//             printf("no cmd infile: (null)\n");
//         cmd_list = cmd_list->next;
//     }
// }

void    process_input(t_shell *shell, char *input)
{
    t_token *tokens;
    t_cmd   *cmd_list;
    t_cmd *tmp;
    int i;
    t_suffix_type illegal_type;
    char error_char;
    int status;

    shell->trimmed_prompt = ft_strtrim(input, " \t\n");
    if (!shell->trimmed_prompt || shell->trimmed_prompt[0] == '\0')
        return ;
    if (!lexer(shell))
    {
        shell->status = 2;
        return ;
    }
    tokens = tokenize_prompt(shell->trimmed_prompt);
    if (!tokens)
    {
        shell->status = 2;
        return ;
    }
    if (check_token_syntax(tokens))
    {
        free_tokens(tokens);
        shell->status = 2;
        return ;
    }
    cmd_list = parser(tokens);
    if (!cmd_list)
    {
        free_tokens(tokens);
        shell->status = 2;
        return ;
    }
    illegal_type = SUFFIX_OK;
    error_char = 0;
    if (!expand_all(cmd_list, shell->env, shell->status, &illegal_type, &error_char))
    {
        has_illegal_expansion(illegal_type, error_char);
        free_tokens(tokens);
        free_cmd_list(cmd_list);
        shell->status = 2;
        return ;
    }
    tmp = cmd_list;
    i = 0;
    while (tmp)
    {
        printf("Command %d: %s\n", i, tmp->cmd ? tmp->cmd : "(null)");
        if (tmp->args)
        {
            int j = 0;
            while (tmp->args[j])
            {
                printf("  Arg[%d]: %s\n", j, tmp->args[j]);
                j++;
            }
        }
        tmp = tmp->next;
        i++;
    }
    if (cmd_list)
	{
		// print_cmd_list(cmd_list);
		status = executor(cmd_list, shell);
        shell->status = status;
		//exec_simple(cmd_list, shell->env);
	}
    free_cmd_list(cmd_list);
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
		// line = readline("minishell$ ");
        line = readline(prompt);
		if (!line)
        {
            write(1, "exit\n", 5);
            free(prompt);
            break ;
        }
        free(prompt);
			// break ;
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


