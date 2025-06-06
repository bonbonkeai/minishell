
#include "minishell.h"

t_token *create_token(const char *content, t_token_type type)
{
	t_token *new;
    
    new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
		return (free(new), NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

void add_token(t_token **head, t_token *new)
{
	t_token *curr;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

t_token_type get_token_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (T_PIPE);
	if (!ft_strcmp(s, "<"))
		return (T_INPUT);
	if (!ft_strcmp(s, "<<"))
		return (T_HEREDOC);
	if (!ft_strcmp(s, ">"))
		return (T_OUTPUT);
	if (!ft_strcmp(s, ">>"))
		return (T_APPEND);
	return (T_WORD);
}

int get_operator_token(const char *line, int i, t_token **tokens)
{
	char	op[3];
	char	op2[2];

	if (!line[i])
		return (0);
	if (line[i] == '>' || line[i] == '<')
	{
		if (line[i] == line[i + 1])
        {
			op[0] = line[i];
            op[1] = line[i];
            op[2] = '\0';
			add_token(tokens, create_token(op, get_token_type(op)));
			return (2);
		}
		else
		{
			op2[0] = line[i];
            op2[1] = '\0';
			add_token(tokens, create_token(op2, get_token_type(op2)));
			return (1);
		}
	}
	if (line[i] == '|')
	{
		add_token(tokens, create_token("|", T_PIPE));
		return (1);
	}
	return (0);
}

int get_word_token(const char *line, int i, t_token **tokens)
{
	int j;
	int in_squote;
	int in_dquote;
	char *word;

    j = 0;
    in_squote = 0;
    in_dquote = 0;
	while (line[i + j])
	{
		if (line[i + j] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i + j] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		else if (!in_squote && !in_dquote && (ft_isspace(line[i + j]) || ft_strchr("<>|", line[i + j])))
			break;
		j++;
	}
	if (j == 0)
		return (0);
	word = ft_substr(line, i, j);
	if (!word)
		return (free(word), 0);
	if (word[0] == '\0')
	{
		free(word);
		return (j);
	}
	// if (!word || word[0] == '\0')
	// {
	// 	free(word);
	// 	return (j);
	// }
	add_token(tokens, create_token(word, T_WORD));
	free(word);
	return (j);
}

t_token *tokenize_prompt(const char *line)
{
	t_token *tokens;
	int i;
	int skip;

    tokens = NULL;
    i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if ((skip = get_operator_token(line, i, &tokens)) > 0)
			i += skip;
		else
			i += get_word_token(line, i, &tokens);
	}
	return (tokens);
}

void free_tokens(t_token *tok)
{
	t_token *tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->content)
		{
			// printf("[free] Token content: %s\n", tok->content);
			free(tok->content);
		}
		free(tok);
		tok = tmp;
	}
}

int check_token_syntax(t_token *t)
{
	if (!t)
		return (ft_fprintf(2, "minishell: empty input\n"), 1);
	if (t->type == T_PIPE)
		return (ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n"), 1);
	while (t)
	{
		if (t->type == T_PIPE)
		{
			if (!t->next || t->next->type == T_PIPE)
				return (ft_fprintf(2, "minishell: syntax error near unexpected token `||'\n"), 1);
		}
		if (is_red_type(t->type))
		{
			if (!t->next)
				return (ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n"), 1);
			if (t->next->type != T_WORD)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n", t->next->content);
				return (1);
			}
		}
		t = t->next;
	}
	return (0);   
}
