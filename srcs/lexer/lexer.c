#include "minishell.h"

int is_empty_command(const char *input)
{
    int i;
    
    i = 0;
    while (input[i])
    {
        if (!ft_isspace(input[i]))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int is_specific_case(t_shell *s)
{
    if (!s->trimmed_prompt)
        return (TRUE);
    if (ft_strcmp(s->trimmed_prompt, "~") == 0)
    {
        s->status = 126;
        ft_putstr_fd("minishell: ~: Is a directory\n", 2);
        return (TRUE);
    }
    if (!ft_strcmp(s->trimmed_prompt, "\"\"") || !ft_strcmp(s->trimmed_prompt, "''"))
    {
        s->status = 127;
        ft_putstr_fd("minishell: : command not found\n", 2);
        return (TRUE);
    }
    return (FALSE);
}

int check_syntax(const char *input)
{
    int in_squote;
    int in_dquote;
    int i;

    in_squote = 0;
    in_dquote = 0;
    i = 0;
    while (input[i])
    {
        toggle_quote(input[i], &in_squote, &in_dquote);
        if (!in_squote && !in_dquote && is_invalid_operator(input, i))
            return (TRUE);
        i++;
    }
    return (check_quotes_closed(in_squote, in_dquote));
}

void toggle_quote(char ch, int *in_squote, int *in_dquote)
{
    if (ch == '\'' && !(*in_dquote))
        *in_squote = !(*in_squote);
    else if (ch == '"' && !(*in_squote))
        *in_dquote = !(*in_dquote);
}

int is_invalid_operator(const char *input, int i)
{
    if ((input[i] == '>' || input[i] == '<' ) && input[i + 1] == '\0')
        return (syntax_error_newline(), TRUE);
    if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
        return (syntax_error('>'), TRUE);
    if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
        return (syntax_error_newline(), TRUE);
    if (input[i] == '|' && input[i + 1] == '|')
        return (syntax_error_pipex("||"), TRUE);
    if (input[i] == '>' && input[i + 1] == '<')
        return (syntax_error('<'), TRUE);
    if (input[i] == '<' && input[i + 1] == '>')
        return (syntax_error_newline(), TRUE);
    if (input[i] == '<' && input[i + 1] == '|')
        return (syntax_error('|'), TRUE);
    return (FALSE);
}

void syntax_error(char unexpected)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, &unexpected, 1);
    write(2, "'\n", 2);
}

void syntax_error_pipex(char *unexpected)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
    write(2, unexpected, ft_strlen(unexpected));
    write(2, "'\n", 2);
}

int check_quotes_closed(int in_squote, int in_dquote)
{
    if (in_squote)
    {
        ft_putstr_fd("minishell: unexpected EOF while looking for matching '\n", 2);
        return (TRUE);
    }
    if (in_dquote)
    {
        ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
        return (TRUE);
    }
    return (FALSE);
}

int is_pipe_error(const char *s)
{
	int len;
	
	if (!s)
		return (FALSE);
	len = ft_strlen(s) - 1;
	if (s[0] == '|')
		return (syntax_error('|'), TRUE);
	if (s[len] == '|' || s[len] == '<' || s[len] == '>')
		return (syntax_error_newline(), TRUE);
	return (FALSE);
}

void	syntax_error_newline(void)
{
	write(2, "minishell: syntax error near unexpected token `newline'\n", 57);
}

int lexer(t_shell *shell)
{
    if (is_empty_command(shell->trimmed_prompt))
        return (FALSE);
    if (is_specific_case(shell))
        return (FALSE);
    if (check_syntax(shell->trimmed_prompt))
    {
        shell->status = 2;
        return (FALSE);
    }
    if (is_pipe_error(shell->trimmed_prompt))
    {
        shell->status = 2;
        return (FALSE);
    }
    return (TRUE);
}


