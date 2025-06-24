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
        free(cmd->infile);
        cmd->infile = ft_strdup(file);
        cmd->heredoc = 0;
        free(cmd->heredoc_limiter);
        cmd->heredoc_limiter = NULL;
    }
    else if (!ft_strcmp(op, "<<"))
    {
        free(cmd->heredoc_limiter);
        cmd->heredoc_limiter = ft_strdup(file);
        free(cmd->infile);
        cmd->infile = ft_strdup(file);
        if (!cmd->heredoc_limiter || !cmd->infile)
        {
            free(cmd->heredoc_limiter);
            cmd->heredoc_limiter = NULL;
            free(cmd->infile);
            cmd->infile = NULL;
            return ;
        }
        cmd->heredoc = 1;
        if ((file[0] == '\'' && file[ft_strlen(file) - 1] == '\'') ||
            (file[0] == '"' && file[ft_strlen(file) - 1] == '"'))
            cmd->heredoc_expand = 0;
        else
            cmd->heredoc_expand = 1;
    }
}


// void handle_input_redir(t_cmd *cmd, char *op, char *file)
// {
//     char *tmp;

//     if (!op || !file || !cmd)
//         return ;
//     tmp = ft_strdup(file);
//     if (!tmp)
//         return ;
//     if (!ft_strcmp(op, "<"))
//     {
//         if (cmd->infile)
//             free(cmd->infile);
//         cmd->infile = tmp;
//         cmd->heredoc = 0;
//         if (cmd->heredoc_limiter) 
//         {
//             free(cmd->heredoc_limiter);
//             cmd->heredoc_limiter = NULL;
//         }
//     }
//     else if (!ft_strcmp(op, "<<"))
//     {
//         if (cmd->heredoc_limiter)
//             free(cmd->heredoc_limiter);
//         cmd->heredoc_limiter = tmp;
//         if (cmd->infile)
//         {
//             free(cmd->infile);
//             cmd->infile = NULL;
//         }
//         if (cmd->infile)
//             free(cmd->infile);
//         cmd->infile = ft_strdup(tmp);
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
    if (!ft_strcmp(op, "<<"))
        return ;
    tmp = ft_strdup(file);
    if (!tmp)
        return ;
    if (cmd->outfile)
    {
        free(cmd->outfile);
        cmd->outfile = NULL;
    }
    cmd->outfile = tmp;
    if (!ft_strcmp(op, ">"))
        cmd->append = 0;
    else if (!ft_strcmp(op, ">>"))
        cmd->append = 1;
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
    // free(tmp);
// }

void resolve_redir(t_cmd *cmd)
{
    int i;
    char *op;
    char *file;

    i = 0;
    if (!cmd)
        return ;
    if (!cmd->red)
        return ;
    while (cmd->red[i] && cmd->red[i + 1])
    {
        op = cmd->red[i];
        file = cmd->red[i + 1];
        handle_input_redir(cmd, op, file);
        handle_output_redir(cmd, op, file);
        i += 2;
    }
}

// void resolve_redir(t_shell *sh)
// {
//     int i;
//     char *op;
//     char *file;

//     i = 0;
//     if (!sh->cmd)
//         return ;
//     if (!sh->cmd->red)
//         return ;
//     while (sh->cmd->red[i] && sh->cmd->red[i + 1])
//     {
//         op = sh->cmd->red[i];
//         file = sh->cmd->red[i + 1];
//         handle_input_redir(sh, op, file);
//         handle_output_redir(sh, op, file);
//         i += 2;
//     }
// }

void    add_redir(t_cmd *cmd, char *op, char *target)
{
    int len;
    char **new_red;
    int i;
    int j;

    if (!op || !target)
    {
        ft_fprintf(2, "minishell: syntax error near unexpected token\n");
        return ;
    }
    len = 0;
    while (cmd->red && cmd->red[len])
        len++;
    new_red = malloc(sizeof(char *) * (len + 3));
    if (!new_red)
        return ;
    i = 0;
    while (i < len)
    {
        new_red[i] = ft_strdup(cmd->red[i]);
        if (!new_red[i])
        {
            while (--i >= 0)
                free(new_red[i]);
            free(new_red);
            return ;
        }
        i++;
    }
    while (i < len)
    {
        new_red[i] = cmd->red[i];
        i++;
    }
    new_red[len] = ft_strdup(op);
    if (!new_red[len])
    {
        while (--len >= 0)
            free(new_red[len]);
        free(new_red);
        return ;
    }
    new_red[len + 1] = ft_strdup(target);
    if (!new_red[len + 1])
    {
        while (--len >= 0)
            free(new_red[len]);
        free(new_red);
        return ;
    }
    new_red[len + 2] = NULL;
    if (cmd->red)
    {
        j = 0;
        while (cmd->red[j])
            free(cmd->red[j++]);
        free(cmd->red);
    }
    cmd->red = new_red;
}

// void    add_redir(t_shell *sh, char *op, char *target)
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
//     while (sh->cmd->red && sh->cmd->red[len])
//         len++;
//     new_red = malloc(sizeof(char *) * (len + 3));
//     if (!new_red)
//         return ;
//     i = 0;
//     while (i < len)
//     {
//         new_red[i] = ft_strdup(sh->cmd->red[i]);
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
//         new_red[i] = sh->cmd->red[i];
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
//     if (sh->cmd->red)
//     {
//         j = 0;
//         while (sh->cmd->red[j])
//             free(sh->cmd->red[j++]);
//         free(sh->cmd->red);
//     }
//     sh->cmd->red = new_red;
// }