#include "minishell.h"

void print_result(const char *input, int result)
{
    printf("Input: \"%s\"\n", input);
    if (result)
        printf("Lexer Success: No syntax error detected.\n");
    else 
        printf("Lexer Failed: Syntax error or special case detected.\n");
    printf("--------------------------------------------------\n");
}

void run_lexer_test(const char *input, t_shell *shell)
{
    int result;

    shell->trimmed_prompt = ft_strdup(input);
    if (!shell->trimmed_prompt)
    {
        perror("ft_strdup");
        return ;
    }
    result = lexer(shell);
    print_result(input, result);
    free(shell->trimmed_prompt);
    shell->trimmed_prompt = NULL;
}


void run_all_lexer_tests(t_shell *shell)
{
    int i;
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
        "cat <| file.txt"
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
        "echo \"hello\" | grep h > out.txt",
        "ls -l | grep .c >> result.txt",
        NULL
    };
    i = 0;
    while (tests[i])
    {
        run_lexer_test(tests[i], shell);
        i++;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    t_shell *shell;
    
    shell = init_shell(envp);
    if (!shell)
    {
        fprintf(stderr, "Failed to init shell\n");
        return (EXIT_FAILURE);
    }

    printf("Starting LEXER TESTS...\n\n");
    run_all_lexer_tests(shell);
    free_shell(shell);
    return EXIT_SUCCESS;
}

