#include "minishell.h"

const char *token_type_str(t_token_type type)
{
    switch (type)
    {
        case T_WORD: return "T_WORD";
        case T_PIPE: return "T_PIPE";
        case T_INPUT: return "T_INPUT";
        case T_OUTPUT: return "T_OUTPUT";
        case T_APPEND: return "T_APPEND";
        case T_HEREDOC: return "T_HEREDOC";
        default: return "UNKNOWN";
    }
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-10s  Type: %d\n", tokens->content, tokens->type);
		tokens = tokens->next;
	}
}

void run_tokenizer_test(const char *input, t_shell *shell)
{
	t_token *tokens;

    printf("Input: \"%s\"\n", input);
    shell->trimmed_prompt = ft_strdup(input);
    if (!shell->trimmed_prompt)
    {
        perror("ft_strdup");
        return ;
    }
    if (!lexer(shell))
    {
        printf("Lexer rejected the input. Skipping tokenizer.\n\n");
        return ;
    }
    tokens = tokenize_prompt(shell->trimmed_prompt);
    if (!tokens)
    {
        printf("Tokenizer failed to produce tokens.\n\n");
        return ;
    }
	if (check_token_syntax(tokens))
    {
        printf("Syntax error detected. Skipping...\n\n");
        free_tokens(tokens);
        free(shell->trimmed_prompt);
        return ;
    }
    print_tokens(tokens);
    free_tokens(tokens);
    printf("--------------------------------------------------\n\n");
}

void run_all_tokenizer_tests(t_shell *shell)
{
	int		i;

    const char *tests[] = {
		"      ",
        "~",
        "\"\"",
        "''",
        "<",
        ">",
        "|",
        "cat <<<",
        "cat >>>",
        "cat > || ls",
        "cat ><",
        "cat <>",
        "| ls",
        "ls |",
        "cat <",
        "cat >",
		"cat <| file.txt",
        "echo 'unclosed",
        "echo \"unclosed2",
        "echo 'hello\"world'hi",
        "echo \">>>\"",
        "echo \"<>\"",
        "echo \"ls |\"",
        "echo \"'>>>'\"",
        "echo \"'h'\"",
        "echo >| file",
        "echo \"hello world\"",
		"echo 'hello | world'",
        "echo \"hello\" | grep h > out.txt",
        "ls -l | grep .c >> result.txt",
        "cat < infile",
        "echo hello > outfile",
        "grep hi >> log",
        "cat << EOF",
        "ls | wc -l",
        "ls    -l     /tmp",
        "cat << EOF | grep \"pattern\" > result.txt",
        NULL
    };
    i = 0;
    while (tests[i])
    {
        run_tokenizer_test(tests[i], shell);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell *shell = init_shell(envp);
    if (!shell)
    {
        fprintf(stderr, "Failed to initialize shell\n");
        return (EXIT_FAILURE);
    }
    printf("Running tokenizer tests...\n\n");
    run_all_tokenizer_tests(shell);
    free_shell(shell);
    return (EXIT_SUCCESS);
}

/*int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_shell	*shell;
    char    *input;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	input = readline("Input command to tokenize: ");
	while (input)
	{
		shell->trimmed_prompt = ft_strtrim(input, " \t\n");
		if (!shell->trimmed_prompt)
			break;
		tokens = tokenize_prompt(shell->trimmed_prompt);
		if (!tokens)
			printf("No tokens found.\n");
		else
			print_tokens(tokens);
		free_tokens(tokens);
		free(shell->trimmed_prompt);
		shell->trimmed_prompt = NULL;
		free(input);
		input = readline("Input command to tokenize: ");
	}
	free_shell(shell);
	return (0);
}*/