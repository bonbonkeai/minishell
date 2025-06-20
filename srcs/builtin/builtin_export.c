/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhuang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:21:45 by jinhuang          #+#    #+#             */
/*   Updated: 2025/06/20 17:42:48 by jinhuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_var_asin(char *arg, char **key, char **value, int *append)
{
	char	*plus_eq;
	char	*eq;

	plus_eq = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (plus_eq)
	{
		*append = 1;
		*key = ft_strndup(arg, plus_eq - arg);
		*value = ft_strdup(plus_eq + 2);
	}
	else
	{
		eq = ft_strchr(arg, '=');
		if (eq)
		{
			*append = 0;
			*key = ft_strndup(arg, eq - arg);
			*value = ft_strdup(eq + 1);
		}
		else
		{
			*key = ft_strdup(arg);
			*value = ft_strdup("");
		}
	}	
}

void	env_set_var(char *key, char *value, t_env **env, int append)
{
	t_env	*cur;
	t_env	*new;
	char	*new_val;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			if (append)
			{
				new_val = ft_strjoin(cur->value, value);
				free(cur->value);
				cur->value = new_val;
			}
			else
			{
				free(cur->value);
				cur->value = ft_strdup(value);
			}
			return ;
		}
		if (cur->next == NULL) // 找到尾节点
			break;
		cur = cur->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (*env == NULL) // 链表为空，直接赋值头指针
		*env = new;
	else // 链表非空，尾节点的 next 指向新节点
		cur->next = new;
}

/* static int	compare_env(const void *a, const void *b)
{
	t_env	*env_a;
	t_env	*env_b;

	env_a = *(t_env **)a;
	env_b = *(t_env **)b;
	return (ft_strcmp(env_a->key, env_b->key));
}
 */
static void	export_print_env(t_env *env)
{
	t_env	*cur = env;
	t_env	**env_array;
	int		count = 0;
	int		i = 0;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	env_array = malloc(sizeof(t_env *) * count);
	if (!env_array)
		return ;
	cur = env;
	while (cur)
	{
		env_array[i++] = cur;
		cur = cur->next;
	}
	bubble_sort_env(env_array, count);
	i = 0;
	while (i < count)
	{
		if (env_array[i]->value && env_array[i]->value[0] != '\0')
    		ft_printf("export %s=\"%s\"\n", env_array[i]->key, env_array[i]->value);
		else
    		ft_printf("export %s\n", env_array[i]->key);

		i++;
	}
	free(env_array);
}

	
int	builtin_export(char **argv, t_env **env)
{
	int	i;
	int	status;
	char	*key;
	char	*value;
	int	append;

	i = 1;
	status = EXIT_SUCCESS;
	if (!argv[1])
	{
		export_print_env(*env);
		return (status);
	}
	if (argv[1] && argv[1][0] == '-')
    {
        if (argv[1][1] != 'f' && argv[1][1] != 'n' && argv[1][1] != '\0')
        {
           printf("bash: export: -%c: invalid option\n", argv[1][1]);
		   printf("export: usage: export [-fn] [name[=value] ...] or export -p\n");
		   return (EXIT_FAILURE);
        }
    }
	while (argv[i])
	{
		split_var_asin(argv[i], &key, &value, &append);
		if (!is_valid_var_name(key))
		{
			ft_perror_export(argv[i]);
			status = EXIT_FAILURE;
			free(key);
			free(value);
			i++;
			continue;
		}
		else
			env_set_var(key, value, env, append);
		free(key);
		free(value);
		i++;
	}
	return (status);
}
