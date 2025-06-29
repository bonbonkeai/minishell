/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:45:05 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:45:07 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_redir_array(char **array, int count)
{
    int i;

    if (!array)
        return ;
    i = 0;
    while (i < count)
    {
        free(array[i]);
        i++;
    }
    free(array);
}

char **init_new_redir_array(t_cmd *cmd, int len)
{
    char **new_red;
    int i;

    new_red = malloc(sizeof(char *) * (len + 3));
    if (!new_red)
        return (NULL);
    i = 0;
    while (i < len)
    {
        new_red[i] = ft_strdup(cmd->red[i]);
        if (!new_red[i])
        {
            free_redir_array(new_red, i);
            return (NULL);
        }
        i++;
    }
    return (new_red);
}

int append_op_and_target(char **new_red, int len, char *op, char *target)
{
    new_red[len] = ft_strdup(op);
    if (!new_red[len])
        return (0);
    new_red[len + 1] = ft_strdup(target);
    if (!new_red[len + 1])
        return (0);
    new_red[len + 2] = NULL;
    return (1);
}

static void	update_heredoc_info(t_cmd *cmd, char *op, char *target)
{
	if (ft_strcmp(op, "<<") == 0)
	{
		if (cmd->heredoc_limiter)
			free(cmd->heredoc_limiter);
		cmd->heredoc_limiter = ft_strdup(target);
		cmd->heredoc = 1;
	}
}

void add_redir(t_cmd *cmd, char *op, char *target)
{
    char **new_red;
    int len;

    if (!op || !target)
    {
        ft_fprintf(2, "minishell: syntax error near unexpected token\n");
        return ;
    }
    update_heredoc_info(cmd, op, target);
    len = count_redirs(cmd->red);
    new_red = init_new_redir_array(cmd, len);
    if (!new_red)
        return ;
    if (!append_op_and_target(new_red, len, op, target))
    {
        free_redir_array(new_red, len + 2);
        return ;
    }
    free_paths(cmd->red);
    cmd->red = new_red;
}

// void    add_redir(t_cmd *cmd, char *op, char *target)
// {
//     int len;
//     char **new_red;
//     int i;
//     int j;

//     if (!op || !target)
//     {
//         ft_fprintf(2, "minishell: syntax error near unexpected token\n");
//         return ;
//     }
//     len = 0;
//     while (cmd->red && cmd->red[len])
//         len++;
//     new_red = malloc(sizeof(char *) * (len + 3));
//     if (!new_red)
//         return ;
//     i = 0;
//     while (i < len)
//     {
//         new_red[i] = ft_strdup(cmd->red[i]);
//         if (!new_red[i])
//         {
//             while (--i >= 0)
//                 free(new_red[i]);
//             free(new_red);
//             return ;
//         }
//         i++;
//     }
//     while (i < len)
//     {
//         new_red[i] = cmd->red[i];
//         i++;
//     }
//     new_red[len] = ft_strdup(op);
//     if (!new_red[len])
//     {
//         while (--len >= 0)
//             free(new_red[len]);
//         free(new_red);
//         return ;
//     }
//     new_red[len + 1] = ft_strdup(target);
//     if (!new_red[len + 1])
//     {
//         while (--len >= 0)
//             free(new_red[len]);
//         free(new_red);
//         return ;
//     }
//     new_red[len + 2] = NULL;
//     if (cmd->red)
//     {
//         j = 0;
//         while (cmd->red[j])
//             free(cmd->red[j++]);
//         free(cmd->red);
//     }
//     cmd->red = new_red;
// }
