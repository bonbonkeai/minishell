/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:38 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:45:40 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// char *extract_single_quoted(const char *input, int *i, char quote)
// {
// 	int start;
// 	char *quoted;

// 	start = *i;
// 	while (input[*i] && input[*i] != quote)
// 		(*i)++;
// 	if (!input[*i])
// 		return NULL;
// 	quoted = strndup(&input[start], *i - start);
// 	(*i)++;
// 	return quoted;
// }

// char *merge_quoted_tokens(const char *input)
// {
// 	int i;
// 	char *merged;
// 	char quote;
// 	char *quoted;

//     i = 0;
//     merged = ft_strdup("");
//     if (!merged)
//         return (NULL);
// 	while (input[i])
// 	{
// 		if (is_quote(input[i]))
// 		{
// 			quote = input[i++];
// 			quoted = extract_single_quoted(input, &i, quote);
// 			if (!quoted)
// 				return (free(merged), NULL);
// 			merged = ft_strjoin_free(merged, quoted);
// 			free(quoted);
// 		}
// 		else
// 		{
// 			int start = i;
// 			while (input[i] && !is_quote(input[i]) && !ft_isspace(input[i]))
// 				i++;
// 			quoted = ft_strndup(&input[start], i - start);
// 			merged = ft_strjoin_free(merged, quoted);
// 			free(quoted);
// 		}
// 	}
// 	return merged;
// }

// char *ft_strjoin_free(char *s1, const char *s2)
// {
// 	char *res = ft_strjoin(s1, s2);
// 	free(s1);
// 	return res;
// }

// static int is_mergeable(t_token *a, t_token *b)
// {
// 	if (!a || !b)
// 		return (0);
// 	if (a->type != b->type)
// 		return (0);
// 	if (a->type == T_WORD || a->type == T_SINGLE_QUOTED || a->type == T_DOUBLE_QUOTED)
// 		return (1);
// 	return (0);
// }

// static void merge_content(t_token *a, t_token *b)
// {
// 	char *tmp;
// 	if (!a || !b)
// 		return ;
// 	tmp = ft_strjoin(a->content, b->content);
//     if (!tmp)
//         return ;
// 	free(a->content);
// 	a->content = tmp;
// }
// // 
// // void merge_adjacent_quoted_tokens(t_token **head)
// // {
// // 	t_token *curr;
// // 	t_token *next;

// // 	if (!head || !*head)
// // 		return ;
// // 	curr = *head;
// // 	while (curr && curr->next)
// // 	{
// // 		next = curr->next;
// // 		if (is_mergeable(curr, next))
// // 		{
// // 			merge_content(curr, next);
// // 			curr->next = next->next;
// // 			free(next->content);
// // 			free(next);
// // 		}
// // 		else
// // 		{
// // 			curr = curr->next;
// // 		}
// // 	}
// // }



// void merge_adjacent_quoted_tokens(t_token **head)
// {
// 	t_token *curr;
// 	t_token *next;

// 	if (!head || !*head)
// 		return ;
// 	curr = *head;
// 	while (curr && curr->next)
// 	{
// 		next = curr->next;
// 		if (is_mergeable(curr, next))
// 		{
// 			printf("Merging: [%s] + [%s]\n", curr->content, next->content);
// 			merge_content(curr, next);
// 			curr->next = next->next;
// 			free(next->content);
// 			free(next);
// 		}
// 		else
// 		{
// 			curr = curr->next;
// 		}
// 	}
// }





