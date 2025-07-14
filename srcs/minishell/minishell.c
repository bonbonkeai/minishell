/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:32 by jdu               #+#    #+#             */
/*   Updated: 2025/07/14 14:46:18 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_arg_with_space(char *joined, char *arg, int is_last)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(joined, arg);
	free(joined);
	if (!tmp)
		return (NULL);
	if (is_last)
		return (tmp);
	result = ft_strjoin(tmp, " ");
	free(tmp);
	if (!result)
		return (NULL);
	return (result);
}

static char	*ft_join_argv(int argc, char **argv)
{
	int		i;
	char	*joined;

	i = 0;
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	while (i < argc)
	{
		joined = join_arg_with_space(joined, argv[i], i == argc - 1);
		if (!joined)
			return (NULL);
		i++;
	}
	return (joined);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*shell;
// 	char	*input;

// 	shell = init_shell(envp);
// 	if (!shell)
// 	{
// 		write(2, "Error: failed to initialize shell\n", 34);
// 		return (EXIT_FAILURE);
// 	}
// 	if (argc > 1)
// 	{
// 		input = ft_join_argv(argc - 1, argv + 1);
// 		if (!input)
// 		{
// 			write(2, "Error: failed to join input args\n", 33);
// 			return (free_shell(shell), EXIT_FAILURE);
// 		}
// 		process_input(shell, input);
// 		return (free(input), free_shell(shell), EXIT_SUCCESS);
// 	}
// 	minishell_loop(shell);
// 	return (free_shell(shell), EXIT_SUCCESS);
// }

static void	cleanup_readline(void)
{
	rl_clear_history();
	rl_cleanup_after_signal();
}

static int	handle_script_input(t_shell *shell, int argc, char **argv)
{
	char	*input;
	int		status;

	input = ft_join_argv(argc - 1, argv + 1);
	if (!input)
	{
		write(2, "Error: failed to join input args\n", 33);
		free_shell(shell);
		cleanup_readline();
		return (EXIT_FAILURE);
	}
	process_input(shell, input);
	status = shell->status;
	free(input);
	free_shell(shell);
	cleanup_readline();
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		status;

	shell = init_shell(envp);
	if (!shell)
	{
		write(2, "Error: failed to initialize shell\n", 34);
		return (EXIT_FAILURE);
	}
	if (argc > 1)
		return (handle_script_input(shell, argc, argv));
	minishell_loop(shell);
	status = shell->status;
	free_shell(shell);
	cleanup_readline();
	return (status);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	*shell;
// 	char	*input;
// 	int		status;

// 	shell = init_shell(envp);
// 	if (!shell)
// 	{
// 		write(2, "Error: failed to initialize shell\n", 34);
// 		return (EXIT_FAILURE);
// 	}
// 	if (argc > 1)
// 	{
// 		input = ft_join_argv(argc - 1, argv + 1);
// 		if (!input)
// 		{
// 			write(2, "Error: failed to join input args\n", 33);
// 			return (free_shell(shell), EXIT_FAILURE);
// 		}
// 		process_input(shell, input);
// 		status = shell->status;
// 		return (free(input), free_shell(shell), status);
// 	}
// 	minishell_loop(shell);
// 	status = shell->status;
// 	return (free_shell(shell), status);
// }
