/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:45:18 by jdu               #+#    #+#             */
/*   Updated: 2025/07/09 14:24:29 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_cmd *cmd, t_shell *sh, char *target)
{
	int		fd[2];
	char	*lim;
	char	*heredoc_content;

	if (pipe(fd) == -1)
		return (perror("pipe"), 1);
	lim = set_should_expand(sh, target);
	heredoc_content = get_heredoc_content(target, lim, sh);
	if (!heredoc_content)
		return (close(fd[0]), close(fd[1]), 1);
	write(fd[1], heredoc_content, ft_strlen(heredoc_content));
	close(fd[1]);
	free(heredoc_content);
	if (cmd->heredoc_fd != -1)
		close(cmd->heredoc_fd);
	cmd->heredoc_fd = fd[0];
	return (0);
}

static int	process_cmd_heredocs(t_cmd *cmd, t_shell *sh, \
	t_suffix_type *out_type, char *error_char)
{
	int	i;

	i = 0;
	while (cmd->red && cmd->red[i] && cmd->red[i + 1])
	{
		if (!ft_strcmp(cmd->red[i], "<<"))
		{
			if (handle_heredoc(cmd, sh, cmd->red[i + 1]))
				return (1);
		}
		i += 2;
	}
	cmd = sh->cmd;
	while (cmd)
	{
		if (cmd->args && !expand_tab(cmd->args, sh, out_type, error_char))
			return (1);
		if (cmd->red && !expand_tab(cmd->red, sh, out_type, error_char))
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	expand_heredoc_in_cmd_list(t_shell *sh, \
		t_suffix_type *out_type, char *error_char)
{
	t_cmd	*curr;

	curr = sh->cmd;
	while (curr)
	{
		if (process_cmd_heredocs(curr, sh, out_type, error_char))
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*expand_var_here(char *input, t_shell *sh)
{
	t_expansion	exp;
	char		*expbuf;

	if (!input || !sh)
		return (NULL);
	if (!init_expand(&exp, input, sh->status))
		return (free(input), NULL);
	while (input[exp.i] != '\0')
	{
		if (expand_var_here_check(input, &exp, sh))
			return (free(input), free(exp.buf), NULL);
		if (exp.len >= exp.size && !handle_buffer(&exp))
			return (free(input), free(exp.buf), NULL);
	}
	exp.buf[exp.len] = '\0';
	expbuf = ft_strdup(exp.buf);
	if (!expbuf)
		return (free(input), NULL);
	free_expansion(&exp);
	return (free(input), expbuf);
}

int	expand_var_here_check(char *input, t_expansion *exp, t_shell *sh)
{
	if (input[exp->i] == '$' && valid_exp(input[exp->i + 1]))
	{
		if (!handle_dollar(input, exp, sh->env))
			return (1);
	}
	else
		exp->buf[exp->len++] = input[exp->i++];
	return (0);
}
