/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:44:57 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:44:58 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_input_redir(t_cmd *cmd, char *op, char *file)
{
    if (!op || !file || !cmd)
        return ;
    if (!ft_strcmp(op, "<"))
    {
        if (cmd->infile)
            free(cmd->infile);
        cmd->infile = ft_strdup(file);
    }
}

// void handle_input_redir(t_cmd *cmd, char *op, char *file)
// {
//     if (!op || !file || !cmd)
//         return ;
//     if (!ft_strcmp(op, "<"))
//     {
//         free(cmd->infile);
//         cmd->infile = ft_strdup(file);
//         cmd->heredoc = 0;
//         free(cmd->heredoc_limiter);
//         cmd->heredoc_limiter = NULL;
//     }
//     else if (!ft_strcmp(op, "<<"))
//     {
//         free(cmd->heredoc_limiter);
//         cmd->heredoc_limiter = ft_strdup(file);
//         free(cmd->infile);
//         cmd->infile = ft_strdup(file);
//         if (!cmd->heredoc_limiter || !cmd->infile)
//         {
//             free(cmd->heredoc_limiter);
//             cmd->heredoc_limiter = NULL;
//             free(cmd->infile);
//             cmd->infile = NULL;
//             return ;
//         }
//         cmd->heredoc = 1;
//         if ((file[0] == '\'' && file[ft_strlen(file) - 1] == '\'') ||
//             (file[0] == '"' && file[ft_strlen(file) - 1] == '"'))
//             cmd->heredoc_expand = 0;
//         else
//             cmd->heredoc_expand = 1;
//     }
// }


void handle_output_redir(t_cmd *cmd, char *op, char *file)
{
    char    *tmp;

    if (!cmd || !op || !file)
        return ;
    tmp = ft_strdup(file);
    if (!tmp)
        return ;
    if (!ft_strcmp(op, ">"))
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = tmp;
        cmd->append = 0;
    }
    else if (!ft_strcmp(op, ">>"))
    {
        if (cmd->outfile)
            free(cmd->outfile);
        cmd->outfile = tmp;
        cmd->append = 1;
    }
}
// void handle_output_redir(t_shell *sh, char *op, char *file)
// {
//     char    *tmp;

//     if (!sh->cmd || !op || !file)
//         return ;
//     tmp = ft_strdup(file);
//     if (!tmp)
//         return ;
//     if (!ft_strcmp(op, ">"))
//     {
//         if (sh->cmd->outfile)
//             free(sh->cmd->outfile);
//         sh->cmd->outfile = tmp;
//         sh->cmd->append = 0;
//     }
//     else if (!ft_strcmp(op, ">>"))
//     {
//         if (sh->cmd->outfile)
//             free(sh->cmd->outfile);
//         sh->cmd->outfile = tmp;
//         sh->cmd->append = 1;
//     }
//     // free(tmp);
// }

void resolve_redir(t_cmd *cmd)
{
    int i;
    char *op;
    char *file;

    i = 0;
    if (!cmd || !cmd->red)
        return ;
    while (cmd->red[i] && cmd->red[i + 1])
    {
        op = cmd->red[i];
        file = cmd->red[i + 1];
        if (!ft_strcmp(op, "<"))
            handle_input_redir(cmd, op, file);
        else if (!ft_strcmp(op, ">") || !ft_strcmp(op, ">>"))
            handle_output_redir(cmd, op, file);
        i += 2;
    }
}

void	touch_all_output_files(t_cmd *cmd)
{
	int		fd;
	int		i;

	if (!cmd || !cmd->red)
		return ;
	i = 0;
	while (cmd->red[i])
	{
		if (ft_strcmp(cmd->red[i], ">") == 0 || ft_strcmp(cmd->red[i], ">>") == 0)
		{
			if (cmd->red[i + 1])
			{
				fd = open(cmd->red[i + 1], O_WRONLY | O_CREAT, 0644);
				if (fd >= 0)
					close(fd);
				i++;
			}
		}
		i++;
	}
}

int count_redirs(char **red)
{
    int len;
    
    len = 0;
    while (red && red[len])
        len++;
    return (len);
}


