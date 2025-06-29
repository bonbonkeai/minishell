/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:47:32 by jdu               #+#    #+#             */
/*   Updated: 2025/06/19 13:47:34 by jdu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*ft_join_argv(int argc, char **argv)
// {
// 	int		i;
// 	char	*joined;
// 	char	*tmp;
// 	char	*with_space;

// 	i = 0;
// 	joined = ft_strdup("");
// 	if (!joined)
// 		return (NULL);
// 	while (i < argc)
// 	{
// 		tmp = ft_strjoin(joined, argv[i]);
// 		free(joined);
// 		if (!tmp)
// 			return (NULL);
// 		if (i < argc - 1)
// 		{
// 			with_space = ft_strjoin(tmp, " ");
// 			free(tmp);
// 			if (!with_space)
// 				return (NULL);
// 			joined = with_space;
// 		}
// 		else
// 			joined = tmp;
// 		i++;
// 	}
// 	return (joined);
// }

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

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
    char *input;

	shell = init_shell(envp);
	if (!shell)
    {
        write(2, "Error: failed to initialize shell\n", 34);
		return (EXIT_FAILURE);
    }
    signal_handle();
	if (argc > 1)
	{
        input = ft_join_argv(argc - 1, argv + 1);
		if (!input)
		{
			write(2, "Error: failed to join input args\n", 33);
			return (free_shell(shell), EXIT_FAILURE);
		}
		process_input(shell, input);
		return (free(input), free_shell(shell), EXIT_SUCCESS);
	}
	minishell_loop(shell);
	return (free_shell(shell), EXIT_SUCCESS);
}


