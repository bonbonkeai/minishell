/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:29 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:45:30 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
