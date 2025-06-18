#include "minishell.h"

void print_cmd_list(t_cmd *cmd)
{
	int i = 0;

	if (!cmd)
	{
    	printf("[print_cmd_list] received NULL cmd\n");
    	return ;
	}
	while (cmd)
	{
		printf("=== Command %d ===\n", i++);
		printf("Command: %s\n", cmd->cmd ? cmd->cmd : "(null)");
		printf("Args:\n");
		for (int j = 0; cmd->args && cmd->args[j]; j++)
			printf("  [%d] %s\n", j, cmd->args[j]);
		printf("Infile: %s\n", cmd->infile ? cmd->infile : "(none)");
		printf("Outfile: %s (append: %d)\n", cmd->outfile ? cmd->outfile : "(none)", cmd->append);
		printf("Heredoc: %s\n", cmd->heredoc ? "yes" : "no");
		printf("--------\n");
		cmd = cmd->next;
	}
}

void run_parser_test(const char *input, t_shell *shell)
{
	t_token *tokens;
	t_cmd   *cmd_list;

	printf("Input: \"%s\"\n", input);
	shell->trimmed_prompt = ft_strdup(input);
	if (!shell->trimmed_prompt || shell->trimmed_prompt[0] == '\0')
		return ;
	if (!lexer(shell))
	{
		printf("Lexer rejected input.\n\n");
		return ;
	}
	tokens = tokenize_prompt(shell->trimmed_prompt);
	if (!tokens)
	{
		printf("Tokenization failed.\n\n");
		return ;
	}
	if (check_token_syntax(tokens))
	{
		printf("Syntax error detected.\n\n");
		free_tokens(tokens);
		return ;
	}
	cmd_list = parser(tokens);
	if (!cmd_list)
	{
		printf("Parser failed to build command list.\n\n");
		free_tokens(tokens);
		return ;
	}
	print_cmd_list(cmd_list);
	free_cmd_list(cmd_list);
	free_tokens(tokens);
	printf("==================================================\n\n");
}

void run_all_parser_tests(t_shell *shell)
{
	const char *tests[] = 
    {
		"echo hello world",
		"ls -l | grep c",
		"ls\t-l",
		"< hello echo > world",
		"< hello > world echo",
		">hello<world echo",
		"cat < infile > outfile",
		"echo a >> file | grep a",
		"echo 'hello\"world'hi",
        "echo \">>>\"",
        "echo \"<>\"",
        "echo \"ls |\"",
        "echo \"'>>>'\"",
        "echo \"'h'\"",
		"echo '>'",
		"echo \">\"",
		"echo '|'",
		"echo \"|\"",
		"echo '<infile'",
		"echo 'a >> file'",
		"echo a | grep b | wc -l | sort > result.txt",
		"ls -l | grep txt | awk '{print $1}'",
		"echo \"a\" \"b\" \"c\" | cat -e",
		"echo '>' > file",
		"echo '|' | cat",
		"echo <<EOF",
		"echo \"hello\\nworld\"",
		"echo       ",
		"\"echo      \"",
		"echo     a     b",
		"echo hello>file",
		"cat<infile|grep",
		"echo    >    outfile",
		"cat < infile > | grep",
		"echo hello | | grep e",
		"cat < infile > outfile |",
		"echo < < >>",
		"echo << >>",
		"echo < < hello",
		"     ",
		"",
		"\"\"",
		"<",
		">",
		"|",
		"echo a > | grep a",
		"echo a < | grep a",
		"echo hello || grep e",
		"cat <",
		"cat >",
		"ls |",
		"| ls",
		"cat <>",
		"cat ><",
		"cat <<< test",
		"cat < < < test",
		"cat >>> test",
		"cat > > > test",
		"echo 'unclosed",
        "echo \"unclosed2",
		NULL
	};
	int i = 0;
	while (tests[i])
		run_parser_test(tests[i++], shell);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_shell *shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);

	printf("Running parser tests...\n\n");
	run_all_parser_tests(shell);
	free_shell(shell);
	return (EXIT_SUCCESS);
}
